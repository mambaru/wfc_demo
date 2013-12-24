#pragma once

#include "types_json.hpp"
#include <demo/api/generate.hpp>
#include <wfc/json/json.hpp>
#include <wfc/json/name.hpp>

namespace wamba{ namespace demo{

namespace request{
  
  struct generate_json
  {
    FAS_NAME(size)
    
    typedef wfc::json::object<
      generate,
      fas::type_list_n<
        wfc::json::member<n_size, generate, size_t, &generate::size>
      >::type
    > type;
  };
}

namespace response
{
  struct generate_json
  {
    FAS_NAME(data)
    
    typedef wfc::json::object<
      generate,
      fas::type_list_n<
        wfc::json::member<n_data, generate, data_ptr,    &generate::data, data_ptr_json >
      >::type
    > type;
  };
}

}}
