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
    
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  struct get_json
  {
    FAS_NAME(name)
    FAS_NAME(data)
    FAS_NAME(status)
    
    typedef wfc::json::object<
      get,
      fas::type_list_n<
        /*wfc::json::member<n_name, get, std::string, &get::name>,*/
        wfc::json::member<n_data, get, std::string, &get::data >,
        wfc::json::member<n_status, get, bool,      &get::status >
      >::type
    > type;
    
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}
