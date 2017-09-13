#pragma once

#include <pingpong/ipinger.hpp>
#include <pingpong/iponger.hpp>
#include <pingpong/api/ball_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace demo{ namespace pingpong{ namespace service{
  
JSONRPC_TAG(ping)
JSONRPC_TAG(play)
JSONRPC_TAG(pong)

template<typename Base>
class ponger_interface: public Base
{
public:
  typedef Base super;
  typedef typename super::io_id_t io_id_t;
  virtual void ping(ball::ptr req, ball::handler cb ) override
  {
    this->template call<_ping_>( std::move(req), cb, nullptr);
  }
};

struct pinger_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<ipinger>,
  wfc::jsonrpc::interface_<iponger2>,
  wfc::jsonrpc::call_method<_ping_, ball_json, ball_json>,
  wfc::jsonrpc::invoke_method< _play_,  ball_json, ball_json, ipinger, &ipinger::play>,
  wfc::jsonrpc::invoke_method2< 
    _pong_, 
    ball_json, ball_json,
    ball, ball,
    ipinger, &ipinger::pong,
    iponger2, &iponger2::ping
  >
>
{
};

}}}
