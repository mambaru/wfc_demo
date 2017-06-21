//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pinger.hpp"
#include <pingpong/iponger.hpp>
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>
#include <atomic>
#include <memory>
#include <chrono>
#include <iomanip>


#define PINGER_LOG_MESSAGE(message) WFC_LOG_MESSAGE("pinger", message)
#define PINGER_LOG_DEBUG(message)   WFC_LOG_DEBUG("pinger", message)

namespace demo{ namespace pingpong{

void pinger::initialize() 
{
  std::lock_guard<std::mutex> lk(_mutex);
  for (const auto& name : this->options().target_list )
    _targets.push_back( this->get_target<iponger>(name)  );
}

pinger::target_list pinger::get_target_list() const
{
  std::lock_guard<std::mutex> lk(_mutex);
  return _targets;
}

void pinger::play(ball::ptr req, ball::handler cb) 
{
  if ( this->notify_ban<ball>(req, cb ) )
    return;
  
  auto pcount = std::make_shared< std::atomic<size_t> >();
  auto ptotal = std::make_shared< std::atomic<size_t> >();
  auto tlist = this->get_target_list();
  *pcount = tlist.size();
  for (auto wt : tlist )
  {
    if ( auto t = wt.lock() )
    {
      auto rereq = std::make_unique<ball>( *req );
      ++rereq->count;
      t->ping( std::move(req), [pcount, ptotal, cb](ball::ptr res)
      {
        if ( res!=nullptr )
          *ptotal+=res->count;
        --(*pcount);
        if ( *pcount == 0 )
        {
          res->count = *ptotal;
          cb( std::move(res) );
        }
      } , 0, this->shared_from_this() );
    }
  }
}

void pinger::pong( ball::ptr req, ball::handler cb, io_id_t, ball_handler reping )
{
  if ( this->notify_ban<ball>(req, cb ) )
    return;
  
  if ( req->power == 0 )
    cb( std::move(req) );
  --req->power;

  auto rereq = std::make_unique<ball>( *req );
  ++rereq->count;
  reping( std::move(rereq), [cb](ball::ptr req)
  {
    cb( std::move(req) );
  });
}

}}
