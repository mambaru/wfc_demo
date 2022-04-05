#pragma once

#include <demo/idemo.hpp>
#include <demo/api/get_json.hpp>
#include <demo/api/get_hashed_json.hpp>
#include <demo/api/multiget_json.hpp>
#include <demo/api/multiget_hashed_json.hpp>
#include <demo/api/multiget_hashed2_json.hpp>
#include <demo/api/set_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace damba{ namespace demo{

JSONRPC_TAG(set)
JSONRPC_TAG(get)
JSONRPC_TAG(multiget)
JSONRPC_TAG(get_hashed)
JSONRPC_TAG(multiget_hashed)
JSONRPC_TAG(multiget_hashed2)

struct gateway_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::interface_<idemo>,
  wfc::jsonrpc::call_method< _set_,      request::set_json,      response::set_json>,
  wfc::jsonrpc::call_method< _get_,      request::get_json,      response::get_json>,
  wfc::jsonrpc::call_method< _multiget_, request::multiget_json, response::multiget_json>,
  wfc::jsonrpc::call_method< _get_hashed_, request::get_hashed_json, response::get_hashed_json>,
  wfc::jsonrpc::call_method< _multiget_hashed_, request::multiget_hashed_json, response::multiget_hashed_json>,
  wfc::jsonrpc::call_method< _multiget_hashed2_, request::multiget_hashed2_json, response::multiget_hashed2_json>
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

  virtual void multiget(request::multiget::ptr req, response::multiget::handler cb ) override
  {
    this->template call< _multiget_ >( std::move(req), cb, nullptr);
  }

  virtual void get_hashed(request::get_hashed::ptr req, response::get_hashed::handler cb ) override
  {
    this->template call< _get_hashed_ >( std::move(req), cb, nullptr);
  }

  virtual void multiget_hashed(request::multiget_hashed::ptr req, response::multiget_hashed::handler cb ) override
  {
    this->template call< _multiget_hashed_ >( std::move(req), cb, nullptr);
  }

  virtual void multiget_hashed2(request::multiget_hashed2::ptr req, response::multiget_hashed2::handler cb ) override
  {
    this->template call< _multiget_hashed2_ >( std::move(req), cb, nullptr);
  }
};

}}
