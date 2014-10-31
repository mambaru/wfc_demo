#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{

namespace request
{
  struct get_range 
  {
    std::string from;
    std::string to;
    size_t offset = 0;
    size_t limit = 10;
  };
}

namespace response
{
  struct get_range
  {
    std::vector<data_type> result;
  };
}

}}
