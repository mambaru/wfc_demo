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
#include <chrono>

#define PINGPONG_LOG_MESSAGE(message) WFC_LOG_MESSAGE("pingpong", message)

namespace wamba{ namespace pingpong{

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
        if ( pong_reqester!=nullptr )
        {
          ::wamba::pingpong::pong_send_( std::move(res), std::move(cb), std::move(pong_reqester) );
        }
        else if (cb != nullptr )
        {
          cb( std::move(res) );
        }
      }
      else if ( res != nullptr )
      {
        ping_counter += res->ping_count;
      }
    };
  }
}

void pingpong::reconfigure()
{
  auto& opt = this->options();
  _deny_pong = opt.deny_pong;
  _stress_ping = opt.stress_ping;

  PINGPONG_LOG_MESSAGE("void pingpong::reconfigure()  _stress_ping= " << _stress_ping)
  _targets.clear();
  for ( auto name: opt.target_list)
  {
    if (auto p = this->global()->registry.get<ipingpong>(name))
    {
      _targets.push_back(p);
    }
  }
  
  this->global()->after_start.push_back([this]()
  {
    this->stress_ping_();
  });
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
    //p->pong(std::make_unique<request::pong>(), nullptr);
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
  if ( cb == nullptr ) 
    return;

  auto res = std::make_unique<response::pong>();
  res->ping_count = req->ping_count;
  res->pong_count = req->pong_count+1;
  cb( std::move(res) );
}

void pingpong::stress_ping_( )
{
  //PINGPONG_LOG_MESSAGE("void pingpong::stress_ping_( size_t stress_ping)")
  using namespace std::placeholders;
  size_t size = _stress_ping;
  for ( size_t i=0; i < size; ++i)
  {
    auto req = std::make_unique<request::ping>();
    auto start = std::chrono::high_resolution_clock::now();
    this->ping2(std::move(req), this->wrap( std::bind(&pingpong::stress_result_, this, _1, start) ) , 0, nullptr );
  }
}

void pingpong::stress_result_( response::ping::ptr, std::chrono::high_resolution_clock::time_point start )
{
  auto finish = std::chrono::high_resolution_clock::now();
  //auto interval = start - finish;
  auto tm_ms = std::chrono::duration_cast< std::chrono::nanoseconds >( finish - start ).count();
  auto rate = tm_ms > 0 ? 1000000000.0/tm_ms : -1 ;
  PINGPONG_LOG_MESSAGE("STRESS RESULT!!! " << rate << " " << tm_ms)
  this->global()->io_service.post( this->wrap( [this]()
  {
    auto start = std::chrono::high_resolution_clock::now();
    using namespace std::placeholders;
    auto req = std::make_unique<request::ping>();
    this->ping2(std::move(req), this->wrap( std::bind(&pingpong::stress_result_, this, _1, start) ) , 0, nullptr );
  }));
}

}}
