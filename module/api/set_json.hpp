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
    JSON_NAME(name)
    JSON_NAME(value)
    JSON_NAME(hash)
    
    typedef wfc::json::object<
      set,
      fas::type_list_n<
        wfc::json::member<n_name, set, std::string, &set::name>,
        wfc::json::member<n_value, set, std::string, &set::value >,
        wfc::json::member<n_hash, set, bool, &set::hash >
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
