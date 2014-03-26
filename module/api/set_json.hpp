#pragma once

#include "types_json.hpp"
#include <demo/api/set.hpp>
#include <wfc/json/json.hpp>
#include <wfc/json/name.hpp>

namespace wamba{ namespace demo{

namespace request
{
  struct set_json
  {
    FAS_NAME(name)
    FAS_NAME(data)
    
    typedef wfc::json::object<
      set,
      fas::type_list_n<
        wfc::json::member<n_name, set, std::string, &set::name>,
        wfc::json::member<n_data, set, data_type,    &set::data, data_type_json >
      >::type
    > type;
    
    typedef type::target     target;
    typedef type::serializer serializer;

  };
}

namespace response
{
  struct set_json
  {
    FAS_NAME(status)
   
    typedef wfc::json::object<
      set,
      fas::type_list_n<
        wfc::json::member<n_status, set, bool, &set::status>
      >::type
    > type;
    
    typedef type::target     target;
    typedef type::serializer serializer;

  };
}

}}
