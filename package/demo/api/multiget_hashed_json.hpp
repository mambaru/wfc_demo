#pragma once

#include <demo/api/multiget_hashed.hpp>
#include <wfc/json.hpp>

namespace demo{

namespace request
{
  struct multiget_hashed_json
  {
    JSON_NAME(keys)

    typedef wfc::json::object<
      multiget_hashed,
      wfc::json::member_list<
        wfc::json::member<
          n_keys, 
          multiget_hashed, 
          std::set<std::string>, 
          &multiget_hashed::keys, 
          wfc::json::array< std::set< wfc::json::value< std::string> > > 
        >
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  struct multiget_hashed_json
  {
    JSON_NAME(values)
    
    typedef wfc::json::object<
      multiget_hashed,
      wfc::json::member_list<
        wfc::json::member<
          n_values,  
          multiget_hashed, 
          multiget_hashed::map_type, 
          &multiget_hashed::values, 
          wfc::json::dict_map< 
            wfc::json::pointer< 
              std::shared_ptr<size_t>,
              wfc::json::value<size_t> 
            >
          >
        >
      >
    > type;
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}
