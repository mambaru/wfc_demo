#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{
  
namespace request
{
  struct set 
  {
    std::string name;
    data_type data;
    bool hash = false;
  };  
}

namespace response
{
  struct set
  {
    bool status = false;
  };
}

}}
