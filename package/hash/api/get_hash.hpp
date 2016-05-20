#pragma once

#include <hash/api/types.hpp>

namespace wamba{ namespace demo{ namespace hash{

namespace request
{
  struct get_hash 
  {
    data_type value;
    typedef std::unique_ptr<get_hash> ptr;
  };
}

namespace response
{
  struct get_hash 
  {
    bool status = false;
    hash_type value = 0;
    typedef std::unique_ptr<get_hash> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}}
