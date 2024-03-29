#pragma once

#include <demo/api/multiget_hashed2.hpp>
#include <wfc/json.hpp>

namespace damba{ namespace demo{

namespace request
{
  struct multiget_hashed2_json
  {
    JSON_NAME(keys)

    typedef wfc::json::object<
      multiget_hashed2,
      wfc::json::member_list<
        wfc::json::member<
          n_keys,
          multiget_hashed2,
          std::vector<std::string>,
          &multiget_hashed2::keys,
          wfc::json::array< std::vector< wfc::json::value< std::string> > >
        >
      >
    > meta;

    typedef meta::target     target;
    typedef meta::serializer serializer;
  };
}

namespace response
{
  struct multiget_hashed2_json
  {
    JSON_NAME(values)

    typedef wfc::json::object<
      multiget_hashed2,
      wfc::json::member_list<
        wfc::json::member<
          n_values,
          multiget_hashed2,
          multiget_hashed2::kv_list,
          &multiget_hashed2::values,
          wfc::json::dict_vector<
            wfc::json::pointer<
              std::shared_ptr<size_t>,
              wfc::json::value<size_t>
            >,
            20
          >
        >
      >
    > meta;
    typedef meta::target     target;
    typedef meta::serializer serializer;
  };
}

}}
