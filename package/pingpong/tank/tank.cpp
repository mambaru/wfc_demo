//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016
//
// Copyright: See COPYING file that comes with this distribution
//

#include "tank.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <condition_variable>

#include <iostream>
#include <atomic>
#include <memory>
#include <chrono>
#include <iomanip>

#define TANK_LOG_MESSAGE(message) WFC_LOG_MESSAGE("tank", message)
#define TANK_LOG_DEBUG(message)   WFC_LOG_DEBUG("tank", message)

namespace demo{ namespace pingpong{

void tank::reconfigure()
{
  _discharge = this->options().discharge;
  _power = this->options().power;
}

void tank::initialize() 
{
  _target = this->get_target<ipinger>( this->options().target );
}

void tank::stop() 
{
  _thread.join();
}

void tank::start()
{
  this->global()->after_start.insert([this]() -> bool 
  {
    this->get_workflow()->post(  
      std::chrono::seconds(3),
      [this]()
      {
        this->_thread = std::thread( std::bind( &tank::fire, this) );
      }, 
      nullptr);
    return false;
  });
}

void tank::fire()
{
  time_t show_time = time(0);
  size_t tatal_rate = 0;
  size_t discharge_count = 0;
    std::mutex m;
    std::condition_variable cond_var;
  while( !this->system_is_stopped() )
  {
    ++discharge_count;
    std::atomic<size_t> dcount;
    dcount = _discharge.load();
    auto start_discharge = clock_t::now();
    if ( auto t = _target.lock() )
    {
      for ( size_t i = 0 ; i <  _discharge; ++i )
      {
        using namespace std::placeholders;
        auto req = std::make_unique<ball>();
        req->power = _power;
        auto tp = clock_t::now();
        if ( dcount == 0) break; // зависаетт иногда приостановке
        t->play( std::move(req),  this->callback([&cond_var, &show_time, tp, &dcount](ball::ptr res)
        {
            if ( res == nullptr || dcount == 0)
            {
              dcount = 0;
              return;
            }
            --dcount;
            if ( dcount == 0 )
              cond_var.notify_one();

            auto now = clock_t::now();
            size_t ms = std::chrono::duration_cast<std::chrono::microseconds>( now - tp).count();
            size_t count = -1;
            if ( res != nullptr )
              count = res->count * 2;
            
            size_t rate = 0;
            if ( ms != 0) 
              rate = count * std::chrono::microseconds::period::den/ ms;
            if ( show_time!=time(0) )
            {
              if ( count != 0 )
                TANK_LOG_MESSAGE("One request. Time " << ms << " microseconds for " << count << " messages. Rate " << rate << " persec")
              else
                TANK_LOG_MESSAGE("One request. Time " << ms << " microseconds Bad Gateway.")
              show_time=time(0);
            }
          },
          [](ball::ptr){
           abort(); 
          })
        );
      }
    }
    /*std::unique_lock<std::mutex> lock(m);

    
    while ( dcount!=0 )
    {
      if ( this->system_is_stopped() )
        break;
      cond_var.wait(lock);
    }*/

    
    while ( dcount!=0 )
    {
      if ( this->system_is_stopped() )
        break;
      std::this_thread::sleep_for( std::chrono::microseconds(1000) );
    }
    
    auto finish_discharge = clock_t::now();
    auto discharge_ms = std::chrono::duration_cast<std::chrono::microseconds>( finish_discharge - start_discharge).count();
    size_t discharge_rate = 0;
    if ( discharge_ms != 0) 
      discharge_rate = _discharge * std::chrono::microseconds::period::den/ discharge_ms;
    tatal_rate += discharge_rate;
    size_t middle_rate = tatal_rate / discharge_count;
    TANK_LOG_MESSAGE("Discharge time " << discharge_ms << " microseconds for " << _discharge 
                      << " messages. Rate " << discharge_rate << " persec ( middle: " << middle_rate << ")" )
    if ( discharge_ms < std::chrono::microseconds::period::den )
    {
      std::this_thread::sleep_for( std::chrono::microseconds( std::chrono::microseconds::period::den - discharge_ms ) );
    }
  }
}

}}
