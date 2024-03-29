//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
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

  std::cout << "ponger::ping power=" << req->power << std::endl;
  auto pcount = std::make_shared< std::atomic<size_t> >();
  auto ptotal = std::make_shared< std::atomic<size_t> >();

  size_t pong_count = _pong_count;
  if ( pong_count == 0 )
  {
    cb( std::move(req) );
  }
  else
  {
    *pcount = pong_count;
    for ( size_t i =0; i < pong_count; ++i )
    {
      using namespace std::placeholders;
      if ( auto p = wp.lock() )
      {
        auto rereq = std::make_unique<ball>( *req );
        ++rereq->count;

        p->pong(
          std::move(rereq),
          [this, pcount, ptotal, cb](ball::ptr res)
          {
            if ( this->global_stop_flag() )
              return;

            if ( res==nullptr )
            {
              DOMAIN_LOG_FATAL("Bad Gateway");
              return;
            }

            auto& ref_count = *pcount;
            if ( ref_count == 0 )
              return;

            *ptotal+=res->count;
            --ref_count;
            if ( ref_count == 0 )
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
  }
}

}}
