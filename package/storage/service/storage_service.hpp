#pragma once

#include <storage/istorage.hpp>
#include <storage/api/get_json.hpp>
#include <storage/api/get_hashed_json.hpp>
#include <storage/api/multiget_json.hpp>
#include <storage/api/multiget_hashed_json.hpp>
#include <storage/api/set_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace demo{ namespace storage {

JSONRPC_TAG(set)
JSONRPC_TAG(get)
JSONRPC_TAG(multiget)
JSONRPC_TAG(get_hashed)
JSONRPC_TAG(multiget_hashed)

struct service_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<istorage>,
  wfc::jsonrpc::invoke_method< _set_,        request::set_json,        response::set_json,      istorage, &istorage::set>,
  wfc::jsonrpc::invoke_method< _get_,        request::get_json,        response::get_json,      istorage, &istorage::get>,
  wfc::jsonrpc::invoke_method< _multiget_,   request::multiget_json, response::multiget_json, istorage, &istorage::multiget>,
  wfc::jsonrpc::invoke_method< _get_hashed_, request::get_hashed_json, response::get_hashed_json, istorage, &istorage::get_hashed>,
  wfc::jsonrpc::invoke_method< _multiget_hashed_, request::multiget_hashed_json, response::multiget_hashed_json, istorage, &istorage::multiget_hashed>
>
{
};

}}
