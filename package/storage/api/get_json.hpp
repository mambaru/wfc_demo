#pragma once

#include <storage/api/get.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{ namespace storage{

namespace request
{
  struct get_json
  {
    JSON_NAME(key)
    JSON_NAME(hash)

    typedef wfc::json::object<
      get,
      wfc::json::member_list<
        wfc::json::member<n_key, get, std::string, &get::key>,
        wfc::json::member<n_hash, get, bool, &get::hash>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  struct get_json
  {
    JSON_NAME(value)
    JSON_NAME(status)

    typedef wfc::json::object<
      get,
      wfc::json::member_list<
        wfc::json::member<n_value,  get, std::string, &get::value >,
        wfc::json::member<n_status, get, bool,        &get::status >
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}}
