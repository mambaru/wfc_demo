#pragma once

#include <storage/api/get_hash.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{ namespace storage{

namespace request
{
  struct get_hash_json
  {
    JSON_NAME(key)

    typedef wfc::json::object<
      get_hash,
      wfc::json::member_list<
        wfc::json::member<n_key, get_hash, std::string, &get_hash::key>
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
    typedef wfc::json::object<
      get_hash,
      wfc::json::member_list<
        wfc::json::member<n_value, get_hash, hash_type, &get_hash::value >
      >
    > type;
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}}
