#pragma once

#include <pingpong/ipinger.hpp>
#include <pingpong/iponger.hpp>
#include <pingpong/api/ball_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace demo{ namespace pingpong{ namespace service{

  /*
  virtual void ping(ball::ptr, ball::handler, io_id_t, std::weak_ptr<ipinger> ) = 0;
  */
  
JSONRPC_TAG(ping)
JSONRPC_TAG(pong)


template<typename Base>
class pinger_interface: public Base
{
public:
  typedef Base super;
  typedef typename super::io_id_t io_id_t;
  typedef typename super::ball_handler ball_handler;

  /*
  virtual void ping(ball::ptr req, ball::handler cb) override
  {
    this->template call<_ping_>( std::move(req), cb);
  }
  */
  
  virtual void pong(ball::ptr req, ball::handler cb, io_id_t, ball_handler ) override
  {
    this->template call<_pong_>( std::move(req), cb, nullptr);
  }
  
/*  
  virtual void pong(ball::ptr req, ball::handler cb ) override
  {
    this->template call<_pong_>( std::move(req), cb, nullptr);
  }
*/
  virtual void play(ball::ptr , ball::handler cb ) override
  {
    if ( cb!=nullptr ) cb(nullptr);
  }
};

struct ponger_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<iponger>,
  wfc::jsonrpc::interface_<ipinger>,
  wfc::jsonrpc::call_method<_pong_, ball_json, ball_json>,
  wfc::jsonrpc::invoke_method1< 
    _ping_, 
    ball_json, ball_json,
    iponger, ipinger,
    &iponger::ping
  >
>
{
};

/*
struct pingpong_serice_handler
  : wfc::jsonrpc::handler<pingpong_method_list>
{
};
*/

/*
struct pingpong_service
  : wfc::jsonrpc::service<pingpong_method_list, pingpong_interface>
{
};
*/

}}}
