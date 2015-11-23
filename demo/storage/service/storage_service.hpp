#pragma once

#include <demo/storage/istorage.hpp>
#include <demo/storage/api/get_json.hpp>
#include <demo/storage/api/set_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace wamba{ namespace demo{ namespace storage {

JSONRPC_TAG(set)
JSONRPC_TAG(get)

struct service_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<istorage>,
  wfc::jsonrpc::invoke_method< _set_,      request::set_json,      response::set_json,      istorage, &istorage::set>,
  wfc::jsonrpc::invoke_method< _get_,      request::get_json,      response::get_json,      istorage, &istorage::get>
>
{
};

}}}
