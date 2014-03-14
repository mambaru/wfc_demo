#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{

namespace request
{
  struct reverse 
  {
    data_ptr data;
  };
}

namespace response
{
  struct reverse 
  {
    data_ptr data;
  };
}

}}
