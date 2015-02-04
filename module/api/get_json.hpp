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
    FAS_NAME(key)
   
    typedef wfc::json::object<
      get,
      fas::type_list_n<
        wfc::json::member<n_key, get, std::string, &get::key>
      >::type
    > type;
    
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  struct get_json
  {
    FAS_NAME(value)
    FAS_NAME(status)
    
    typedef wfc::json::object<
      get,
      fas::type_list_n<
        /*wfc::json::member<n_name, get, std::string, &get::name>,*/
        wfc::json::member<n_value, get, std::string, &get::value >,
        wfc::json::member<n_status, get, bool,      &get::status >
      >::type
    > type;
    
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}
