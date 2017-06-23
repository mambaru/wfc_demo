//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016
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
  const auto* flag = &(this->global()->stop_signal_flag);
  while( !*flag )
  {
    if ( auto t = _target.lock() )
    {
      for ( size_t i = 0 ; i <  _discharge; ++i )
      {
        using namespace std::placeholders;
        auto req = std::make_unique<ball>();
        req->power = _power;
        auto tp = clock_t::now();
        //ball::handler handler = std::bind(&tank::result_handler, this, now, _1);
        //t->play( std::move(req),  handler );
        t->play( std::move(req),  [&show_time,tp](ball::ptr res)
        {
            auto now = clock_t::now();
            size_t ms = std::chrono::duration_cast<std::chrono::microseconds>( now - tp).count();
            size_t count = 0;
            if ( res != nullptr )
              count = res->count * 2;
            size_t rate = 0;
            if ( ms != 0) 
              rate = count * std::chrono::microseconds::period::den/ ms;
            if ( show_time!=time(0) )
            {
              TANK_LOG_MESSAGE("Time " << ms << " microseconds for " << count << " messages. Rate " << rate << " persec")
              show_time=time(0);
            }
          }
        );
      }
    }
  }
}

void tank::result_handler(clock_t::time_point tp, ball::ptr res)
{
  if ( res == nullptr )
    return;

  auto now = clock_t::now();
  size_t ms = std::chrono::duration_cast<std::chrono::microseconds>( now - tp).count();
  size_t count = res->count * 2;
  size_t rate = count * std::chrono::microseconds::period::den/ ms;
  TANK_LOG_MESSAGE("Time " << ms << " microseconds for " << count << " messages. Rate " << rate << " persec")
}

}}
