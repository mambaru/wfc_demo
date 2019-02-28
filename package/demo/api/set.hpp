#pragma once

#include <string>
#include <memory>
#include <functional>

namespace demo{
  
namespace request
{
  struct set 
  {
    std::string key;
    std::string value;
    typedef std::unique_ptr<set> ptr;
    
    static set create_schema() 
    {
      set sch;
      sch.key = "key1";
      sch.value = "value1";
      return sch;
    }
  };
}

namespace response
{
  struct set
  {
    typedef std::unique_ptr<set> ptr;
    typedef std::function< void(ptr)> handler;
    bool status = false;
  };
}

}
