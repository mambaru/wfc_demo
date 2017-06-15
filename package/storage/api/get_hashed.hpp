#pragma once

#include <string>
#include <memory>
#include <functional>

namespace demo{ namespace storage{  

namespace request
{
  struct get_hashed
  {
    std::string key;
    typedef std::unique_ptr<get_hashed> ptr;
  };
}

namespace response
{
  struct get_hashed
  {
    size_t value = 0;
    bool status = false;
    typedef std::unique_ptr<get_hashed> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
