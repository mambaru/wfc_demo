#pragma once

#include <demo/api/set.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{

namespace request
{
  struct set_json
  {
    JSON_NAME(key)
    JSON_NAME(value)
    JSON_NAME(hash)

    typedef wfc::json::object<
      set,
      wfc::json::member_list<
        wfc::json::member<n_key, set, std::string, &set::key>,
        wfc::json::member<n_value, set, std::string, &set::value >,
        wfc::json::member<n_hash, set, bool, &set::hash >
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  struct set_json
  {
    JSON_NAME(status)
    typedef wfc::json::object<
      set,
      wfc::json::member_list<
        wfc::json::member<n_status, set, bool, &set::status>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}