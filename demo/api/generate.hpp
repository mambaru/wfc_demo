#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{

namespace request
{
  struct generate 
  {
    size_t size;
    size_t count = 10;
  };
}

namespace response
{
  struct generate 
  {
    size_t n;
    data_ptr data;
  };
}

}}
