#pragma once

#include <demo/idemo.hpp>
#include "api/generate_json.hpp"
#include "api/reverse_json.hpp"
#include "api/get_json.hpp"
#include "api/set_json.hpp"
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{

JSONRPC_TAG(set)
JSONRPC_TAG(get)
JSONRPC_TAG(generate)
JSONRPC_TAG(reverse)
  
struct method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<idemo>,
  wfc::jsonrpc::invoke_method< _set_,      request::set_json::type,      response::set_json::type,      idemo, &idemo::set>,
  wfc::jsonrpc::invoke_method< _get_,      request::get_json::type,      response::get_json::type,      idemo, &idemo::get>,
  wfc::jsonrpc::invoke_method< _generate_, request::generate_json::type, response::generate_json::type, idemo, &idemo::generate>,
  wfc::jsonrpc::invoke_method< _reverse_,  request::reverse_json::type,  response::reverse_json::type,  idemo, &idemo::reverse>
>
{};

}}


/*
#include "set_method.hpp"
#include "get_method.hpp"
#include "generate_method.hpp"
#include "reverse_method.hpp"
#include "tags.hpp"

#include <fas/type_list.hpp>

namespace wamba{ namespace demo{

struct method_list: fas::type_list_n<
  wfc::jsonrpc::method< _set_,      set_method >, 
  wfc::jsonrpc::method< _get_,      get_method >, 
  wfc::jsonrpc::method< _generate_, generate_method >
>::type {};

}}
*/