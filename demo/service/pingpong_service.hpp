#pragma once

#include <demo/api/ipingpong.hpp>
#include <demo/api/pingpong/ping_json.hpp>
#include <demo/api/pingpong/pong_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace wamba{ namespace pingpong{

JSONRPC_TAG(pong)
JSONRPC_TAG(ping)
JSONRPC_TAG(ping2)

template<typename A>
class pingpong_interface
  : public ::wfc::jsonrpc::interface_implementation<A>
{
public:
  typedef ::wfc::jsonrpc::interface_implementation<A> super;
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
  wfc::jsonrpc::startup_method< ipingpong, ipingpong, &ipingpong::startup >
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

}}
