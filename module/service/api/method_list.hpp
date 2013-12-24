#pragma once

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
