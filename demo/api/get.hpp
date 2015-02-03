#pragma once

#include <demo/api/types.hpp>

namespace wamba{ namespace demo{

namespace request
{
  struct get 
  {
    key_type name;
    typedef std::unique_ptr<get> ptr;
  };
}

namespace response
{
  struct get 
  {
    /*key_type name;*/
    data_type value;
    bool status;
    typedef std::unique_ptr<get> ptr;
    typedef std::function< void(ptr)> callback;
  };
}

}}
