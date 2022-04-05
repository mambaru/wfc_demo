#pragma once

#include <string>
#include <memory>
#include <functional>

namespace damba{ namespace hash{

namespace request
{
  struct get_hash 
  {
    std::string value;
    typedef std::unique_ptr<get_hash> ptr;
  };
}

namespace response
{
  struct get_hash 
  {
    size_t value = 0;
    typedef std::unique_ptr<get_hash> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
