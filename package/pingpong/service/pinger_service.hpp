#pragma once

#include <pingpong/ipinger.hpp>
#include <pingpong/iponger.hpp>
#include <pingpong/api/ball_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace demo{ namespace pingpong{ namespace service{

  /*
virtual void ping(ball::ptr, ball::handler) = 0;
virtual void pong(ball::ptr, ball::handler, io_id_t, ball_handler ) = 0;
  */
  
JSONRPC_TAG(ping)
JSONRPC_TAG(pong)


template<typename Base>
class ponger_interface: public Base
{
public:
  typedef Base super;
  typedef typename super::io_id_t io_id_t;
  //typedef typename super::ball_handler ball_handler;

  /*
  virtual void ping(ball::ptr req, ball::handler cb) override
  {
    this->template call<_ping_>( std::move(req), cb);
  }

  virtual void pong(ball::ptr req, ball::handler cb, io_id_t, ball_handler ) override
  {
    this->template call<_pong_>( std::move(req), cb);
  }
  */
  
  virtual void ping(ball::ptr req, ball::handler cb, io_id_t, std::weak_ptr<ipinger> ) override
  {
    this->template call<_ping_>( std::move(req), cb, nullptr);
  }
};

struct pinger_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<ipinger>,
  //wfc::jsonrpc::peeper<ipinger>,
  wfc::jsonrpc::interface_<iponger>,
  wfc::jsonrpc::invoke_method< _ping_,  ball_json, ball_json, ipinger, &ipinger::ping>/*,
  wfc::jsonrpc::invoke_method2< 
    _pong_, 
    ball_json, ball_json,
    ball, ball,
    ipinger, &ipinger::pong,
    iponger, &iponger::ping
  >*/
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
