#pragma once

#include <storage/api/get_hashed.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{ namespace storage{

namespace request
{
  struct get_hash_json
  {
    JSON_NAME(key)

    typedef wfc::json::object<
      get_hashed,
      wfc::json::member_list<
        wfc::json::member<n_key, get_hashed, std::string, &get_hashed::key>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  struct get_hash_json
  {
    JSON_NAME(value)
    JSON_NAME(status)
    
    typedef wfc::json::object<
      get_hash,
      wfc::json::member_list<
        wfc::json::member<n_status, get_hashed, bool,      &get_hashed::status >,
        wfc::json::member<n_value,  get_hashed, hash_type, &get_hashed::value >
      >
    > type;
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}}
