#pragma once

#include <storage/istorage.hpp>
#include <storage/api/get_json.hpp>
#include <storage/api/get_hash_json.hpp>
#include <storage/api/set_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ namespace storage{ 

JSONRPC_TAG(set)
JSONRPC_TAG(get)
JSONRPC_TAG(get_hash)

struct gateway_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::interface_<istorage>,
  wfc::jsonrpc::call_method< _set_,      request::set_json,      response::set_json>,
  wfc::jsonrpc::call_method< _get_,      request::get_json,      response::get_json>,
  wfc::jsonrpc::call_method< _get_hash_, request::get_hash_json, response::get_hash_json>
>
{
};

template<typename Base>
class storage_interface
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
  
  virtual void get_hash(request::get_hash::ptr req, response::get_hash::handler cb ) override
  {
    this->template call< _get_hash_ >( std::move(req), cb, nullptr);
  }
};

}}}
