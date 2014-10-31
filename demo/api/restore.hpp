#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{

namespace request
{
  struct restore 
  {
  };
}

namespace response
{
  struct restore
  {
    size_t count;
  };
}

}}
