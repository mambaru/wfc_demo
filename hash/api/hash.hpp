#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{
  
namespace request
{
  struct hash
  {
    std::string text;
  };  
}

namespace response
{
  struct hash
  {
    size_t result;
  };
}

}}
