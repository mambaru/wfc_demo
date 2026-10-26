//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2018, 2020, 2022
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <demo/api/set.hpp>
#include <wfc/json.hpp>

namespace damba{ namespace demo{

namespace request
{
  struct set_json
  {
    JSON_NAME(key)
    JSON_NAME(value)

    typedef wfc::json::object<
      set,
      wfc::json::member_list<
        wfc::json::member<n_key,   set, std::string, &set::key>,
        wfc::json::member<n_value, set, std::string, &set::value >
      >
    > meta;

    typedef meta::target     target;
    typedef meta::serializer serializer;
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
        wfc::json::member<n_status,   set, bool, &set::status>
      >
    > meta;

    typedef meta::target     target;
    typedef meta::serializer serializer;
  };
}

}}
