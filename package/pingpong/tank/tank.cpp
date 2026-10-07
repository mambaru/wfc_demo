//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016-2019, 2022, 2024-2026
//
// Copyright: See COPYING file that comes with this distribution
//

#include "tank.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>

#include <iostream>
#include <atomic>
#include <memory>
#include <chrono>
#include <iomanip>

#define TANK_LOG_MESSAGE(message) WFC_LOG_MESSAGE("tank", message)
// #define TANK_LOG_DEBUG(message)   WFC_LOG_DEBUG("tank", message)

namespace damba{ namespace pingpong{

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
  if ( _thread.joinable() )
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
  auto show_time = std::make_shared<time_t>(time(nullptr));
  long tatal_rate = 0;
  long discharge_count = 0;
  while( !this->global_stop_flag() )
  {
    ++discharge_count;
    auto messages_count = std::make_shared<std::atomic<long>>(0);
    auto dcount = std::make_shared<std::atomic<long>>(_discharge.load());
    auto start_discharge = clock_t::now();
    if ( auto t = _target.lock() )
    {
      for ( long i = 0 ; i <  _discharge && !this->global_stop_flag(); ++i )
      {
        auto req = std::make_unique<ball>();
        req->power = _power;
        auto tp = clock_t::now();
        if ( *dcount == 0) break;
        t->play( std::move(req),  this->callback(
          [this, show_time, tp, dcount, messages_count](ball::ptr res)
          {
            if ( this->global_stop_flag() )
              return;

            if ( res==nullptr )
            {
              DOMAIN_LOG_ERROR("tank: Bad Gateway");
            }
            else
            {
              auto now = clock_t::now();
              long ms = std::chrono::duration_cast<std::chrono::microseconds>( now - tp).count();
              long count = res->count * 2;
              *messages_count += count;

              long rate = 0;
              if ( ms != 0)
                rate = count * std::chrono::microseconds::period::den/ ms;
              if ( *show_time!=time(nullptr) )
              {
                *show_time=time(nullptr);
                TANK_LOG_MESSAGE("One request. Time " << ms << " microseconds for " << count << " messages. Rate " << rate << " persec")
              }
            }

            --*dcount;
          })
        );
      }
    }
    else
    {
      *dcount = 0;
    }

    while ( *dcount!=0 )
    {
      if ( this->global_stop_flag() )
        break;
      std::this_thread::sleep_for( std::chrono::microseconds(1000) );
    }

    auto finish_discharge = clock_t::now();
    long discharge_ms = std::chrono::duration_cast<std::chrono::microseconds>( finish_discharge - start_discharge).count();
    long discharge_rate = 0;
    long message_rate = 0;
    if ( discharge_ms != 0)
    {
      discharge_rate = _discharge * std::chrono::microseconds::period::den/ discharge_ms;
      message_rate = *messages_count * std::chrono::microseconds::period::den/ discharge_ms;
    }
    tatal_rate += discharge_rate;
    long middle_rate = tatal_rate / discharge_count;
    TANK_LOG_MESSAGE("Discharge time " << discharge_ms << " microseconds for " << _discharge
                      << " messages. Rate " << discharge_rate << " persec ( middle: " << middle_rate << ")" )
    TANK_LOG_MESSAGE("Messages count " << *messages_count << " messages rps: " << message_rate);
    if ( discharge_ms < std::chrono::microseconds::period::den )
    {
      std::this_thread::sleep_for( std::chrono::microseconds( std::chrono::microseconds::period::den - discharge_ms ) );
    }
  } //while
}

}}
