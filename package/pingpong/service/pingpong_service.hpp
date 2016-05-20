#pragma once

#include <pingpong/ipingpong.hpp>
#include <pingpong/api/ping_json.hpp>
#include <pingpong/api/pong_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace wamba{ namespace pingpong{ namespace service{

JSONRPC_TAG(pong)
JSONRPC_TAG(ping)
JSONRPC_TAG(ping2)

template<typename Base>
class pingpong_interface: public Base
{
public:
  typedef Base super;
  typedef typename super::io_id_t io_id_t;
  typedef typename super::pong_handler pong_handler;

  virtual void ping(request::ping::ptr /*req*/, response::ping::handler cb, io_id_t, std::weak_ptr<ipingpong> ) override
  {
    if ( cb!=nullptr )
      cb(nullptr);
  }

  virtual void ping2(request::ping::ptr, response::ping::handler cb, io_id_t, pong_handler ) override
  {
    if ( cb!=nullptr )
      cb(nullptr);
  }

  virtual void pong(request::pong::ptr req, response::pong::handler cb ) override
  {
    this->template call<_pong_>( std::move(req), cb, nullptr);
  }

  virtual void startup(io_id_t, std::weak_ptr<ipingpong> ) override 
  {
  }
};

struct pingpong_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<ipingpong>,
  wfc::jsonrpc::interface_<ipingpong>,
  wfc::jsonrpc::invoke_method1< _ping_,  request::ping_json, response::ping_json, ipingpong, ipingpong, &ipingpong::ping>,
  wfc::jsonrpc::invoke_method2< _ping2_, 
    request::ping_json, response::ping_json,
    request::pong, response::pong,
    ipingpong, &ipingpong::ping2,
    ipingpong, &ipingpong::pong>,
  wfc::jsonrpc::dual_method<    _pong_, request::pong_json, response::pong_json, ipingpong,  &ipingpong::pong>,

  wfc::jsonrpc::peeper<ipingpong>,
  wfc::jsonrpc::connect_method< ipingpong, ipingpong, &ipingpong::startup >
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
