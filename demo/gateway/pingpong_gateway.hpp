#pragma once

#include <demo/api/ipingpong.hpp>
#include <demo/api/pingpong/ping_json.hpp>
#include <demo/api/pingpong/pong_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace pingpong{

JSONRPC_TAG(ping)
JSONRPC_TAG(ping2)
JSONRPC_TAG(pong)

template<typename A>
class pingpong_interface
  : public ::wfc::jsonrpc::interface_implementation<A>
{
public:
  typedef ::wfc::jsonrpc::interface_implementation<A> super;
  typedef typename super::io_id_t io_id_t;
  typedef typename super::pong_handler pong_handler;

  virtual void ping(request::ping::ptr req, response::ping::handler cb, io_id_t, std::weak_ptr<ipingpong> ) override
  {
    this->template call<_ping_>( std::move(req), cb, nullptr);
  }

  virtual void ping2(request::ping::ptr req, response::ping::handler cb, io_id_t, pong_handler ) override
  {
    this->template call<_ping2_>( std::move(req), cb, nullptr);
  }

  virtual void pong(request::pong::ptr , response::pong::handler cb ) override
  {
    if ( cb!=nullptr )
      cb(nullptr);
  }
  
  virtual void startup(io_id_t, std::weak_ptr<ipingpong> ) override {}
};



struct gateway_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::interface_<ipingpong>,
  wfc::jsonrpc::call_method< _ping_,      request::ping_json,      response::ping_json>,
  wfc::jsonrpc::call_method< _ping2_,      request::ping_json,      response::ping_json>,

#error Тутова не работает 
  wfc::jsonrpc::target<ipingpong>,
  wfc::jsonrpc::invoke_method< _pong_,      request::pong_json,      response::pong_json, ipingpong, &ipingpong::pong>
>
{
};

}}
