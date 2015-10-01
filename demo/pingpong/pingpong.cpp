//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>

namespace wamba{ namespace pingpong{
  
void pingpong::reconfigure()
{
  _targets.clear();
  for ( auto name: this->options().target_list)
  {
    if (auto p = this->global()->registry.get<ipingpong>(name))
    {
      _targets.push_back(p);
      
    }
  }
}

void pingpong::ping(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, std::shared_ptr<ipingpong> ppp)
{
  std::cout << "ping-1-" << std::endl;
  if ( _targets.empty() )
  {
    std::cout << "ping-2-" << std::endl;
    auto pong_req = std::make_unique<request::pong>();
    pong_req->ping_count = req->ping_count + 1;
    pong_req->pong_count = req->pong_count;
    
    std::cout << "ping-3-" << (ppp!=nullptr) << std::endl;
    ppp->pong( std::move(pong_req), [cb](response::pong::ptr res)
    {
      auto ping_res = std::make_unique<response::ping>();
      ping_res->ping_count = res->ping_count + 100;
      ping_res->pong_count = res->pong_count + 100;
      cb( std::move(ping_res) );
    });
  }
  else
  {
    request::ping req_ping;
    req_ping.ping_count = req->ping_count + 1;
    req_ping.pong_count = req->pong_count;

    auto counter = std::make_shared< std::atomic<size_t> >( _targets.size() );
    auto callback = [cb, counter, ppp](response::ping::ptr res)
    {
      --(*counter);
      if ( counter == 0)
      {
        auto pong_req = std::make_unique<request::pong>();
        pong_req->ping_count = res->ping_count + 1;
        pong_req->pong_count = res->pong_count;
        
        ppp->pong( std::move(pong_req), [cb](response::pong::ptr res)
        {
          auto ping_res = std::make_unique<response::ping>();
          ping_res->ping_count = res->ping_count;
          ping_res->pong_count = res->pong_count;
          cb( std::move(ping_res) );
        });
        
        /*
        auto ping_res = std::make_unique<response::ping>();
        ping_res->ping_count = res->ping_count;
        ping_res->pong_count = res->pong_count;
        cb( std::move(ping_res) );
        */
      }
    };
    
    for (auto t : _targets )
    {
      t->ping( std::make_unique<request::ping>(req_ping), callback, io_id, ppp);
    }
  }
}

void pingpong::ping2(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, pong_handler handler) 
{
  std::cout << "ping2-1-" << std::endl;
  if ( _targets.empty() )
  {
    std::cout << "ping2-2-" << std::endl;
    auto pong_req = std::make_unique<request::pong>();
    pong_req->ping_count = req->ping_count + 1;
    pong_req->pong_count = req->pong_count;
    
    std::cout << "ping2-3-" << (handler!=nullptr) << std::endl;
    handler( std::move(pong_req), [cb](response::pong::ptr res)
    {
      if ( cb!=nullptr )
      {
        DOMAIN_LOG_MESSAGE("pingpong::ping2 READY  handler cb!=nullptr")
        auto ping_res = std::make_unique<response::ping>();
        ping_res->ping_count = res->ping_count + 100;
        ping_res->pong_count = res->pong_count + 200;
        cb( std::move(ping_res) );
      }
      else
      {
        DOMAIN_LOG_FATAL("pingpong::ping handler cb==nullptr")
        abort();
      }
    });
  }
  else
  {
    request::ping req_ping;
    req_ping.ping_count = req->ping_count + 1;
    req_ping.pong_count = req->pong_count;

    auto counter = std::make_shared< std::atomic<size_t> >( _targets.size() );
    auto callback = [cb, counter, handler](response::ping::ptr res)
    {
      --(*counter);
      if ( counter == 0)
      {
        auto pong_req = std::make_unique<request::pong>();
        pong_req->ping_count = res->ping_count + 1;
        pong_req->pong_count = res->pong_count;

        handler( std::move(pong_req), [cb](response::pong::ptr res)
        {
          auto ping_res = std::make_unique<response::ping>();
          ping_res->ping_count = res->ping_count;
          ping_res->pong_count = res->pong_count;
          cb( std::move(ping_res) );
        });
      }
    };

    for (auto t : _targets )
    {
      t->ping2( std::make_unique<request::ping>(req_ping), callback, io_id, handler);
    }
  }
}

  
void pingpong::pong(request::pong::ptr req, response::pong::handler cb ) 
{
}

}}
