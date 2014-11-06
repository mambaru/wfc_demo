#pragma once

#include <demo/api/types.hpp>
#include <wfc/json/json.hpp>
#include <vector>

namespace wamba{ namespace demo{

typedef wfc::json::array< 
  std::vector< wfc::json::value<int> >, 10
> data_type_json;

//typedef wfc::json::pointer<data_ptr, data_type_json> data_ptr_json;


}}
