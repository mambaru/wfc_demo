#pragma once

#include <storage/api/types.hpp>

namespace wamba{ namespace demo{ namespace storage{  

namespace request
{
  struct get_hashed
  {
    key_type key;
    typedef std::unique_ptr<get_hash> ptr;
  };
}

namespace response
{
  struct get_hashed
  {
    hash_type value = 0;
    bool status = false;
    typedef std::unique_ptr<get_hashed> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}}
