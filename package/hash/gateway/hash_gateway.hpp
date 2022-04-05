#pragma once

#include <hash/ihash.hpp>
#include <hash/api/get_hash_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace damba{ namespace hash{ 

JSONRPC_TAG(get_hash)

struct gateway_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::interface_<ihash>,
  wfc::jsonrpc::call_method< _get_hash_,      request::get_hash_json,      response::get_hash_json>
>
{};

template<typename Base>
class hash_interface
  : public Base
{
public:
  virtual void get_hash(request::get_hash::ptr req, response::get_hash::handler cb ) override
  {
    this->template call< _get_hash_ >( std::move(req), cb, nullptr);
  }
};

}}
