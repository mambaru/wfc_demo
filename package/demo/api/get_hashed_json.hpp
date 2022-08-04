#pragma once

#include <demo/api/get_hashed.hpp>
#include <wfc/json.hpp>

namespace damba{ namespace demo{

namespace request
{
  struct get_hashed_json
  {
    JSON_NAME(key)

    typedef wfc::json::object<
      get_hashed,
      wfc::json::member_list<
        wfc::json::member<n_key, get_hashed, std::string, &get_hashed::key>
      >
    > meta;

    typedef meta::target     target;
    typedef meta::serializer serializer;
  };
}

namespace response
{
  struct get_hashed_json
  {
    JSON_NAME(value)
    JSON_NAME(status)

    typedef wfc::json::object<
      get_hashed,
      wfc::json::member_list<
        wfc::json::member<n_status, get_hashed, bool,      &get_hashed::status >,
        wfc::json::member<n_value,  get_hashed, size_t, &get_hashed::value >
      >
    > meta;
    typedef meta::target     target;
    typedef meta::serializer serializer;
  };
}

}}
