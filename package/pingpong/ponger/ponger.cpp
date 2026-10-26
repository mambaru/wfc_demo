//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017-2019, 2022, 2024-2026
//
// Copyright: See COPYING file that comes with this distribution
//

#include "ponger.hpp"
#include <pingpong/iponger.hpp>
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>
#include <atomic>
#include <memory>
#include <chrono>
#include <iomanip>


// #define PONGER_LOG_MESSAGE(message) WFC_LOG_MESSAGE("ponger", message)
// #define PONGER_LOG_DEBUG(message)   WFC_LOG_DEBUG("ponger", message)

namespace damba{ namespace pingpong{

void ponger::reconfigure()
{
  _pong_count = this->options().pong_count;
}

void ponger::ping(ball::ptr req, ball::handler cb, io_id_t /*io_id*/, std::weak_ptr<ipinger> wp )
{
  if ( this->notify_ban(req, cb ) )
    return;

  //std::cout << "ponger::ping power=" << req->power << std::endl;
  auto pcount = std::make_shared< std::atomic<size_t> >();
  auto ptotal = std::make_shared< std::atomic<int64_t> >();

  size_t pong_count = _pong_count;
  if ( pong_count == 0 )
  {
    cb( std::move(req) );
    return;
  }

  auto p = wp.lock();
  if ( !p )
  {
    DOMAIN_LOG_ERROR("ponger::ping: pinger is gone");
    cb( nullptr );
    return;
  }

  *pcount = pong_count;
  for ( size_t i =0; i < pong_count; ++i )
  {
    auto rereq = std::make_unique<ball>( *req );
    ++rereq->count;

    p->pong(
      std::move(rereq),
      [this, pcount, ptotal, cb](ball::ptr res)
      {
        if ( this->global_stop_flag() )
          return;

        auto left = --*pcount;
        if ( res==nullptr )
        {
          DOMAIN_LOG_ERROR("ponger::ping: Bad Gateway");
          if ( left == 0 )
            cb( nullptr );
          return;
        }

        *ptotal += res->count;
        if ( left == 0 )
        {
          res->count = *ptotal;
          cb( std::move(res) );
        }
      },
      0,
      nullptr
    );
  }
}

}}
