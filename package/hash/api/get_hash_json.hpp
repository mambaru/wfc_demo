#pragma once

#include <hash/api/get_hash.hpp>
#include <wfc/json.hpp>

namespace damba{ namespace hash{

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
    JSON_NAME(value)
    typedef wfc::json::object<
      get_hash,
      wfc::json::member_list<
        wfc::json::member<n_value,  get_hash, size_t, &get_hash::value>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}
