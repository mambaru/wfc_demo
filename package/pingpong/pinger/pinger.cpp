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
    _targets.push_back( this->get_target<iponger2>(name)  );
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

  auto tlist = this->get_target_list();
  if ( tlist.empty() )
  {
    return cb( std::move(req) );
  }

  auto pwait = std::make_shared< std::atomic<size_t> >();
  auto ptotal = std::make_shared< std::atomic<size_t> >();
  *pwait = tlist.size();
  for (auto wt : tlist )
  {
    if ( auto t = wt.lock() )
    {
      auto rereq = std::make_unique<ball>( *req );
      ++rereq->count;
      --rereq->power;
      t->ping( std::move(rereq), [pwait, ptotal, cb](ball::ptr res)
      {
        if ( *pwait == 0 )
          return;
        if ( res == nullptr )
        {
          *pwait = 0;
          cb(nullptr);
        }
        else
        {
          --(*pwait);
          *ptotal+=res->count;
          if ( *pwait == 0 )
          {
            res->count = *ptotal;
            cb( std::move(res) );
          }
        }
      });
    }
  }
}

void pinger::pong( ball::ptr req, ball::handler cb, io_id_t, ball_handler reping )
{
  if ( this->notify_ban<ball>(req, cb ) )
    return;
  
  if ( req->power == 0 )
  {
    cb( std::move(req) );
  }
  else
  {
    --req->power;
    ++req->count;
    reping( std::move(req), [cb](ball::ptr req)
    {
      cb( std::move(req) );
    });
  }
}

}}
