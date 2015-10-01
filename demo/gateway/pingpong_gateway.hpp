#pragma once

#include <demo/api/ipingpong.hpp>
#include <demo/api/pingpong/ping_json.hpp>
#include <demo/api/pingpong/pong_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace pingpong{

JSONRPC_TAG(ping)
JSONRPC_TAG(ping2)
JSONRPC_TAG(pong)

struct gateway_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::interface_<ipingpong>,
  wfc::jsonrpc::call_method< _ping_,      request::ping_json,      response::ping_json>,
  wfc::jsonrpc::call_method< _ping2_,      request::ping_json,      response::ping_json>
  /*,
  wfc::jsonrpc::call_method< _pong_,      request::pong_json,      response::pong_json>*/
>
{
  virtual void ping(request::ping::ptr req, response::ping::handler cb, io_id_t, std::shared_ptr<ipingpong> ) override
  {
    this->call<_ping_>( std::move(req), cb, nullptr);
  }

  virtual void ping2(request::ping::ptr req, response::ping::handler cb, io_id_t, pong_handler ) override
  {
    this->call<_ping2_>( std::move(req), cb, nullptr);
  }

  virtual void pong(request::pong::ptr req, response::pong::handler cb ) override
  {
    if ( cb!=nullptr )
      cb(nullptr);
  }
  

};

struct gateway_handler
  : wfc::jsonrpc::handler<gateway_method_list>
{
};

struct gateway
  : wfc::jsonrpc::gateway<gateway_handler>
{
  
  virtual void ping(request::ping::ptr req, response::ping::handler cb, io_id_t, std::shared_ptr<ipingpong> ) override
  {
    this->call<_ping_>( std::move(req), cb, nullptr);
  }
  
  virtual void ping2(request::ping::ptr req, response::ping::handler cb, io_id_t, pong_handler ) override
  {
    this->call<_ping2_>( std::move(req), cb, nullptr);
  }

  virtual void pong(request::pong::ptr req, response::pong::handler cb ) override
  {
    if ( cb!=nullptr )
      cb(nullptr);
  }
};

}}
