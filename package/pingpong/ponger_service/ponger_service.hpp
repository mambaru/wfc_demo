#pragma once

#include <pingpong/ipinger.hpp>
#include <pingpong/iponger.hpp>
#include <pingpong/api/ball_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace damba{ namespace pingpong{ namespace service{

JSONRPC_TAG(ping)
JSONRPC_TAG(pong)

template<typename Base>
class pinger_interface: public Base
{
public:
  typedef Base super;
  typedef typename super::io_id_t io_id_t;
  typedef typename super::ball_handler ball_handler;

  virtual void pong(ball::ptr req, ball::handler cb, io_id_t, ball_handler ) override
  {
    this->template call<_pong_>( std::move(req), cb, nullptr);
  }
  
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

}}}
