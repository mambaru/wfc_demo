#pragma once

#include "types_json.hpp"
#include <demo/api/get.hpp>
#include <wfc/json/json.hpp>
#include <wfc/json/name.hpp>

namespace wamba{ namespace demo{

namespace request
{
  struct get_json
  {
    FAS_NAME(name)
   
    typedef wfc::json::object<
      get,
      fas::type_list_n<
        wfc::json::member<n_name, get, std::string, &get::name>
      >::type
    > type;
  };
}

namespace response
{
  struct get_json
  {
    FAS_NAME(name)
    FAS_NAME(data)
    
    typedef wfc::json::object<
      get,
      fas::type_list_n<
        wfc::json::member<n_name, get, std::string, &get::name>,
        wfc::json::member<n_data, get, data_ptr,    &get::data, data_ptr_json >
      >::type
    > type;
  };
}

}}
