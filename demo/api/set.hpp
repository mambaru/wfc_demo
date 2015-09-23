#pragma once

#include <demo/api/types.hpp>

namespace wamba{ namespace demo{
  
namespace request
{
  struct set 
  {
    key_type key;
    data_type value;
    typedef std::unique_ptr<set> ptr;
  };
}

namespace response
{
  struct set
  {
    bool status = false;
    typedef std::unique_ptr<set> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
