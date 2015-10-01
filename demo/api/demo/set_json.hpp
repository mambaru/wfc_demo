#pragma once

#include <demo/api/demo/set.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{

namespace request
{
  struct set_json
  {
    JSON_NAME(key)
    JSON_NAME(value)

    typedef wfc::json::object<
      set,
      wfc::json::member_list<
        wfc::json::member<n_key, set, std::string, &set::key>,
        wfc::json::member<n_value, set, std::string, &set::value >
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
