#pragma once

#include <demo/api/ipingpong.hpp>
#include <demo/api/pingpong/ping_json.hpp>
#include <demo/api/pingpong/pong_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace pingpong{

JSONRPC_TAG(pong)
JSONRPC_TAG(ping)

struct pingpong_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<ipingpong>,
  wfc::jsonrpc::interface_<ipingpong>,
  wfc::jsonrpc::dual_method1< _ping_,      request::ping_json,      response::ping_json,      ipingpong,  &ipingpong::ping>,
  wfc::jsonrpc::invoke_method<  _pong_,      request::pong_json,      response::pong_json,      ipingpong,  &ipingpong::pong>
>
{
  /*
  */
};

struct pingpong_serice_handler
  : wfc::jsonrpc::handler<pingpong_method_list>
{
  virtual void ping(request::ping::ptr req, response::ping::handler cb, io_id_t, std::shared_ptr<ipingpong> ) override
  {
    this->call<_ping_>( std::move(req), cb, nullptr);
  }
  
  virtual void pong(request::pong::ptr req, response::pong::handler cb ) override
  {
    if ( cb!=nullptr )
      cb(nullptr);
  }
};

struct pingpong_service
  : wfc::jsonrpc::service<pingpong_serice_handler>
{
};

}}
