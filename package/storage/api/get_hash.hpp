#pragma once

#include <storage/api/types.hpp>

namespace wamba{ namespace demo{ namespace storage{  

namespace request
{
  struct get_hash
  {
    key_type key;
    typedef std::unique_ptr<get> ptr;
  };
}

namespace response
{
  struct get_hash 
  {
    hash_type value = 0;
    typedef std::unique_ptr<get_hash> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}}
