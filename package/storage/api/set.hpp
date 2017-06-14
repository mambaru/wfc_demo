#pragma once

#include <storage/api/types.hpp>

namespace demo{ namespace storage{
  
namespace request
{
  struct set 
  {
    std::string key;
    std::string value;
    typedef std::unique_ptr<set> ptr;
  };
}

namespace response
{
  struct set
  {
    typedef std::unique_ptr<set> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
