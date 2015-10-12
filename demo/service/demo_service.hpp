#pragma once

#include <demo/api/idemo.hpp>
#include <demo/api/demo/get_json.hpp>
#include <demo/api/demo/set_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ namespace service{

JSONRPC_TAG(set)
JSONRPC_TAG(get)

struct demo_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<idemo>,
  wfc::jsonrpc::invoke_method< _set_,      request::set_json,      response::set_json,      idemo, &idemo::set>,
  wfc::jsonrpc::invoke_method< _get_,      request::get_json,      response::get_json,      idemo, &idemo::get>
>
{
};

}}}