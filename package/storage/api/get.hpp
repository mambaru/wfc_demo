#pragma once

#include <storage/api/types.hpp>

namespace wamba{ namespace demo{ namespace storage{  

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
    bool status = false;
    typedef std::unique_ptr<get> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}}
