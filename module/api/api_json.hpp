#pragma once
#include <demo/api/api.hpp>
#include <fas/functional/tstring.hpp>
#include <wfc/callback/callback_owner.hpp>
#include <wfc/json/json.hpp>
#include <vector>

namespace wamba{ namespace demo{

typedef wfc::json::array< 
  std::vector< wfc::json::value<int> >,
  fas::int_<10>
> data_type_json;

typedef wfc::json::pointer<data_ptr, data_type_json> data_ptr_json;

/// set

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
        wfc::json::member<n_data, set, data_ptr,    &set::data, data_ptr_json >
      >::type
    > type;
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
  };
}

/// get

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

/// reverse

namespace request
{
}

namespace response
{
}

/// generate

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
