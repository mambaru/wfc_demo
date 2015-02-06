#pragma once

#include <demo/api/types.hpp>
#include <unordered_map>

namespace wamba{ namespace demo{

namespace request
{
  struct get 
  {
    key_type key;
    typedef std::unique_ptr<get> ptr;
  };
}

namespace response
{
  struct get 
  {
    data_type value;
    bool status;
    typedef std::unique_ptr<get> ptr;
    typedef std::function< void(ptr)> callback;
  };
}

}}
