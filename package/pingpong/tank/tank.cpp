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
  this->reg_thread();
  time_t show_time = time(nullptr);
  long tatal_rate = 0;
  long discharge_count = 0;
  std::mutex m;
  std::condition_variable cond_var;
  while( !this->system_is_stopped() )
  {
    ++discharge_count;
    std::atomic<long> messages_count;
    messages_count = 0;
    std::atomic<long> dcount;
    dcount = _discharge.load();
    auto start_discharge = clock_t::now();
    if ( auto t = _target.lock() )
    {
      for ( long i = 0 ; i <  _discharge && !this->system_is_stopped(); ++i )
      {
        using namespace std::placeholders;
        auto req = std::make_unique<ball>();
        req->power = _power;
        auto tp = clock_t::now();
        if ( dcount == 0) break; // зависаетт иногда приостановке
        t->play( std::move(req),  this->callback([this, &cond_var, &show_time, tp, &dcount, &messages_count](ball::ptr res)
        {
          if ( this->system_is_stopped() || dcount == 0 )
            return;
          
          if ( res==nullptr )
          {
            DOMAIN_LOG_FATAL("Bad Gateway");
            return;
          }
          
          --dcount;
          if ( dcount == 0 )
            cond_var.notify_one();

          auto now = clock_t::now();
          long ms = std::chrono::duration_cast<std::chrono::microseconds>( now - tp).count();
          long count = -1;
          if ( res != nullptr )
          {
            count = static_cast<long>(res->count * 2);
            messages_count += count;
          }
            
          long rate = 0;
          if ( ms != 0) 
            rate = count * std::chrono::microseconds::period::den/ ms;
          if ( show_time!=time(nullptr) )
          {
            if ( count != 0 )
            {
              TANK_LOG_MESSAGE("One request. Time " << ms << " microseconds for " << count << " messages. Rate " << rate << " persec")
            }
            else
            {
              TANK_LOG_MESSAGE("One request. Time " << ms << " microseconds Bad Gateway.")
              show_time=time(nullptr);
            }
          }
        })
      );
    }
  }

    while ( dcount!=0 )
    {
      if ( this->system_is_stopped() )
        break;
      std::this_thread::sleep_for( std::chrono::microseconds(1000) );
    }
    
    auto finish_discharge = clock_t::now();
    long discharge_ms = std::chrono::duration_cast<std::chrono::microseconds>( finish_discharge - start_discharge).count();
    long discharge_rate = 0;
    if ( discharge_ms != 0) 
      discharge_rate = _discharge * std::chrono::microseconds::period::den/ discharge_ms;
    tatal_rate += discharge_rate;
    long middle_rate = tatal_rate / discharge_count;
    TANK_LOG_MESSAGE("Discharge time " << discharge_ms << " microseconds for " << _discharge 
                      << " messages. Rate " << discharge_rate << " persec ( middle: " << middle_rate << ")" )
    TANK_LOG_MESSAGE("Messages count " << messages_count << " messages rps: " << discharge_rate*messages_count);
    if ( discharge_ms < std::chrono::microseconds::period::den )
    {
      std::this_thread::sleep_for( std::chrono::microseconds( std::chrono::microseconds::period::den - discharge_ms ) );
    }
  } //while
}

}}
