#pragma once

#include <hash/api/hash.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{

namespace request
{
  namespace wj = ::wfc::json;
  
  struct hash_json
  {
    JSON_NAME(text)
    
    typedef wj::object<
      hash,
      fas::type_list_n<
        wj::member<n_text, hash, std::string, &hash::text>
      >::type
    > type;
    
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  namespace wj = ::wfc::json;
  
  struct hash_json
  {
    FAS_NAME(result)
   
    typedef wj::object<
      hash,
      fas::type_list_n<
        wj::member<n_result, hash, size_t, &hash::result>
      >::type
    > type;
    
    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}
