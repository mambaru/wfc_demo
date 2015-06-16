#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{

namespace request
{
  struct inc 
  {
    std::string name;
    int value = 1;
  };
}

namespace response
{
  struct inc
  {
    bool status = false;
    int value = 0;
  };
}

}}
