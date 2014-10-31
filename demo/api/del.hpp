#pragma once

#include <demo/api/types.hpp>
#include <string>

namespace wamba{ namespace demo{

namespace request
{
  struct del
  {
    std::string name;
  };
}

namespace response
{
  struct del
  {
    bool status = false;
  };
}

}}
