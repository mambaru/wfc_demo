#pragma once

#include <demo/api/idemo.hpp>
#include <demo/api/demo/get_json.hpp>
#include <demo/api/demo/set_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ namespace gateway{

JSONRPC_TAG(set)
JSONRPC_TAG(get)

struct demo_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::interface_<idemo>,
  wfc::jsonrpc::call_method< _set_,      request::set_json,      response::set_json>,
  wfc::jsonrpc::call_method< _get_,      request::get_json,      response::get_json>
>
{
};

template<typename Base>
class demo_interface
  : public Base
{
public:
  virtual void set(request::set::ptr req, response::set::handler cb ) override
  {
    this->template call< _set_ >( std::move(req), cb, nullptr);
  }

  virtual void get(request::get::ptr req, response::get::handler cb ) override
  {
    this->template call< _get_ >( std::move(req), cb, nullptr);
  }
};


}}}
