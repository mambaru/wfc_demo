//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017-2019, 2022, 2024-2026
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
#include <vector>
#include <chrono>
#include <iomanip>

// #define PINGER_LOG_MESSAGE(message) WFC_LOG_MESSAGE("pinger", message)
// #define PINGER_LOG_DEBUG(message)   WFC_LOG_DEBUG("pinger", message)

namespace damba{ namespace pingpong{

void pinger::initialize()
{
  std::lock_guard<std::mutex> lk(_mutex);
  auto tl = this->options().target_list;
  auto handler = std::bind(&super::get_target<iponger2>, this, std::placeholders::_1, false);
  std::transform(std::begin(tl), std::end(tl), std::back_inserter(_targets),  handler);
}

pinger::target_list pinger::get_target_list() const
{
  std::lock_guard<std::mutex> lk(_mutex);
  return _targets;
}

void pinger::play(ball::ptr req, ball::handler cb)
{
  if ( this->notify_ban(req, cb ) )
    return;

  auto tlist = this->get_target_list();
  std::vector<std::shared_ptr<iponger2>> targets;
  for (auto wt : tlist)
  {
    if ( auto t = wt.lock() )
      targets.push_back(std::move(t));
  }

  if ( targets.empty() )
  {
    cb( std::move(req) );
    return;
  }

  auto pwait = std::make_shared< std::atomic<size_t> >(targets.size());
  auto ptotal = std::make_shared< std::atomic<int64_t> >(0);
  for (auto& t : targets)
  {
    auto rereq = std::make_unique<ball>( *req );
    ++rereq->count;
    --rereq->power;
    t->ping( std::move(rereq), [this, pwait, ptotal, cb](ball::ptr res)
    {
      if ( this->global_stop_flag() )
        return;

      auto left = --*pwait;
      if ( res==nullptr )
      {
        DOMAIN_LOG_ERROR("pinger::play: Bad Gateway");
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
    });
  }
}

void pinger::pong( ball::ptr req, ball::handler cb, io_id_t, ball_handler reping )
{
  if ( this->notify_ban(req, cb ) )
    return;

  if ( req->power == 0 || !reping )
  {
    cb( std::move(req) );
    return;
  }

  --req->power;
  ++req->count;
  reping( std::move(req), [cb](ball::ptr req1)
  {
    cb( std::move(req1) );
  });
}

}}
