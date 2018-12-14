#pragma once

#include <string>
#include <memory>
#include <functional>

namespace demo{

namespace request
{
  struct get 
  {
    std::string key;
    typedef std::unique_ptr<get> ptr;
  };
}

namespace response
{
  struct get 
  {
    std::string value;
    bool status = false;
    typedef std::unique_ptr<get> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}
