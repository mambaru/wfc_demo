#pragma once

#include <hash/api/get_hash.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{ namespace hash{

namespace request
{
  struct get_hash_json
  {
    JSON_NAME(value)

    typedef wfc::json::object<
      get_hash,
      wfc::json::member_list<
        wfc::json::member<n_value, get_hash, std::string, &get_hash::value >
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
    JSON_NAME(status)
    JSON_NAME(value)
    typedef wfc::json::object<
      get_hash,
      wfc::json::member_list<
        wfc::json::member<n_status, get_hash, bool, &get_hash::status>,
        wfc::json::member<n_value,  get_hash, hash_type, &get_hash::value>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}}
