//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>
#include <atomic>
#include <memory>

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

namespace {
  inline void pong_result_ping(response::ping::handler cb, response::pong::ptr res)
  {
    auto ping_res = std::make_unique<response::ping>();
    ping_res->ping_count = res->ping_count;
    ping_res->pong_count = res->pong_count;
    cb( std::move(ping_res) );
  }

  template<typename T>
  void pong_send_(T req, response::ping::handler cb, ipingpong::pong_handler pong_reqester)
  {
    if ( pong_reqester != nullptr )
    {
      using namespace std::placeholders;
      auto pong_req = std::make_unique<request::pong>();
      pong_req->ping_count = req->ping_count + 1;
      pong_req->pong_count = req->pong_count;
      pong_reqester( std::move(pong_req), std::bind( pong_result_ping, cb, _1 ) );
    }
    else
    {
      auto res = std::make_unique<response::ping>();
      res->ping_count = req->ping_count + 1;
      res->pong_count = req->pong_count;
      cb( std::move(res));
    }
  }

  response::ping::handler make_response_wrapper(size_t size, response::ping::handler cb, ipingpong::pong_handler pong_reqester)
  {
    typedef std::shared_ptr< std::atomic_size_t > size_ptr;
    std::pair<size_ptr, size_ptr> p;
    p.first = std::make_shared< std::atomic_size_t >( size );
    p.second = std::make_shared< std::atomic_size_t >( 0 );
    return [cb, p, pong_reqester](response::ping::ptr res)
    {
      auto& callback_counter = *(p.first);
      auto& ping_counter = *(p.second);
      --callback_counter;
      if ( callback_counter == 0)
      {
        if ( res != nullptr )
        {
          res->ping_count += ping_counter;
        }
        ::wamba::pingpong::pong_send_( std::move(res), std::move(cb), std::move(pong_reqester) );
      }
      else if ( res != nullptr )
      {
        ping_counter += res->ping_count;
      }
    };
  }
  
}


/**
 * Рассылает входящий ping по целям и собирает ответы. 
 * Собрав все ответы, делает запрос pong источнику пинга
 */
void pingpong::reping_(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, pong_handler pong_reqester)
{
  using namespace std::placeholders;
  request::ping req_ping;
  req_ping.ping_count = req->ping_count + 1;
  req_ping.pong_count = req->pong_count;

  auto callback = make_response_wrapper(_targets.size(), std::move(cb), std::move(pong_reqester) );
    
  for (auto t : _targets )
  {
    // TODO: сделать domain::get_io_id;
    std::shared_ptr<pingpong> pthis; // shared_from_this, wthis
    t->ping2( std::make_unique<request::ping>(req_ping), callback, -1, std::bind( &ipingpong::pong, pthis, _1, _2) );
  }
}

void pingpong::ping(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, std::weak_ptr<ipingpong> itf)
{
  using namespace std::placeholders;
  if ( auto pitf = itf.lock() )
  {
    this->ping2(std::move(req), std::move(cb), io_id, std::bind(&ipingpong::pong, pitf, _1, _2) );
  }
}

void pingpong::ping2(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, pong_handler pong_reqester) 
{
  if ( _targets.empty() )
  {
    ::wamba::pingpong::pong_send_( std::move(req), std::move(cb), pong_reqester );
  }
  else
  {
    this->reping_( std::move(req), std::move(cb), io_id, pong_reqester );
  }
}

void pingpong::pong(request::pong::ptr req, response::pong::handler cb ) 
{
  if ( cb == nullptr ) return;
  auto res = std::make_unique<response::pong>();
  res->ping_count = req->ping_count;
  res->pong_count = req->pong_count+1;
  cb( std::move(res) );
}

void pingpong::reg_io(io_id_t io_id, std::weak_ptr<iinterface> witf)
{
  if ( auto p = witf.lock() )
  {
    p->perform_io( ::iow::io::make("Hello World"), 0, nullptr );
  }
}

void pingpong::startup(io_id_t, std::weak_ptr<ipingpong> witf)
{
  if ( auto p = witf.lock() )
  {
    std::cout << "-1- void pingpong::startup(io_id_t, std::weak_ptr<ipingpong> witf)" << std::endl;
    p->pong(std::make_unique<request::pong>(), nullptr);
    std::cout << "-1- void pingpong::startup(io_id_t, std::weak_ptr<ipingpong> witf)" << std::endl;
  }
}

}}
