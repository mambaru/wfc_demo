#pragma once

#include <demo/api/multiget.hpp>
#include <wfc/json.hpp>

namespace damba{ namespace demo{

namespace request
{
  struct multiget_json
  {
    JSON_NAME(keys)

    typedef wfc::json::object<
      multiget,
      wfc::json::member_list<
        wfc::json::member<
          n_keys,
          multiget,
          std::set<std::string>,
          &multiget::keys,
          wfc::json::array< std::set< wfc::json::value< std::string> > >
        >
      >
    > meta;

    typedef meta::target     target;
    typedef meta::serializer serializer;
  };
}

namespace response
{
  struct multiget_json
  {
    JSON_NAME(values)
    typedef wfc::json::pointer< std::shared_ptr<std::string>, wfc::json::value<std::string> > string_pointer_json;
    typedef wfc::json::dict_map< string_pointer_json > dict_json;
    typedef wfc::json::object<
      multiget,
      wfc::json::member_list<
        wfc::json::member< n_values, multiget, multiget::map_type, &multiget::values, dict_json>
      >
    > meta;
    typedef meta::target     target;
    typedef meta::serializer serializer;
  };
}

}}
