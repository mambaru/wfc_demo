#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{

namespace request
{
  struct get 
  {
    std::string name;
  };
}

namespace response
{
  struct get 
  {
    std::string name;
    data_ptr data;
  };
}

}}
