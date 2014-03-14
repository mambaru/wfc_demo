#pragma once

#include "types_json.hpp"
#include <demo/api/reverse.hpp>
#include <wfc/json/json.hpp>
#include <wfc/json/name.hpp>
#include <fas/type_list.hpp>
namespace wamba{ namespace demo{

namespace request
{
  struct reverse_json
  {
    FAS_NAME(data)
    
    typedef wfc::json::object<
      reverse,
      fas::type_list_n<
        wfc::json::member<n_data, reverse, data_ptr,    &reverse::data, data_ptr_json >
      >::type
    > type;
  };
}

namespace response
{
  struct reverse_json
  {
    FAS_NAME(data)
    
    typedef wfc::json::object<
      reverse,
      fas::type_list_n<
        wfc::json::member<n_data, reverse, data_ptr,    &reverse::data, data_ptr_json >
      >::type
    > type;
  };

}

}}
