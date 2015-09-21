#pragma once

#include <demo/api/idemo.hpp>
#include <demo/api/json/get_json.hpp>
#include <demo/api/json/set_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{

JSONRPC_TAG(set)
JSONRPC_TAG(get)

struct demo_method_list1: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::interface_<idemo>,
  wfc::jsonrpc::call_method< _set_,      request::set_json,      response::set_json>,
  wfc::jsonrpc::call_method< _get_,      request::get_json,      response::get_json>
>
{
  /*
    virtual void set(request::set::ptr req, response::set::callback cb ) = 0;
  virtual void get(request::get::ptr req, response::get::callback cb ) = 0;
  */

  //virtual void set(request::set::ptr req, response::set::callback cb ) = 0;
  /*
  virtual void set(request::set::ptr req, response::set::callback cb ) override
  {
    this->call<_set_>( std::move(req), cb, nullptr);
  }
  
  virtual void get(request::get::ptr req, response::get::callback cb ) override
  {
    this->call<_get_>( std::move(req), cb, nullptr);
  }
  */
};

struct demo_gateway_handler
  : wfc::jsonrpc::handler<demo_method_list1>
{
};

struct demo_gateway
  : wfc::jsonrpc::gateway<demo_gateway_handler>
{
  
  virtual void set(request::set::ptr req, response::set::callback cb ) override
  {
    DEBUG_LOG_TRACE("virtual void set(request::set::ptr req, response::set::callback cb ) override")
    this->call<_set_>( std::move(req), cb, nullptr);
  }
  
  virtual void get(request::get::ptr req, response::get::callback cb ) override
  {
    DEBUG_LOG_TRACE("virtual void get(request::get::ptr req, response::get::callback cb ) override")
    this->call<_get_>( std::move(req), cb, nullptr);
  }

};

}}
