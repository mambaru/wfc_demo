#pragma once

#include <demo/idemo.hpp>
#include "api/get_json.hpp"
#include "api/set_json.hpp"
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ namespace service{

//JSONRPC_TAG(push)
JSONRPC_TAG(set)
JSONRPC_TAG(get)
//JSONRPC_TAG(generate)
//JSONRPC_TAG(reverse)
  
struct method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<idemo>,
  wfc::jsonrpc::invoke_method< _set_,      request::set_json,      response::set_json,      idemo, &idemo::set>,
  wfc::jsonrpc::invoke_method< _get_,      request::get_json,      response::get_json,      idemo, &idemo::get>
>
{
};

}}}
