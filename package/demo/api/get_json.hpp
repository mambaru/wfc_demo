#pragma once

#include <demo/api/get.hpp>
#include <wfc/json.hpp>

namespace damba{ namespace demo{

namespace request
{
  struct get_json
  {
    JSON_NAME(key)

    typedef wfc::json::object<
      get,
      wfc::json::member_list<
        wfc::json::member<n_key, get, std::string, &get::key>
      >
    > meta;

    typedef meta::target     target;
    typedef meta::serializer serializer;
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
        wfc::json::member<n_status, get, bool,        &get::status >,
        wfc::json::member<n_value,  get, std::string, &get::value >
      >
    > meta;

    typedef meta::target     target;
    typedef meta::serializer serializer;
  };
}

}}
