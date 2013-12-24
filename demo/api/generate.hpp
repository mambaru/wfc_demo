#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{

namespace request
{
  struct generate 
  {
    size_t size;
  };
}

namespace response
{
  struct generate 
  {
    data_ptr data;
  };
}

}}
