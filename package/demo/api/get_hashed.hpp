#pragma once

#include <string>
#include <memory>
#include <functional>

namespace demo{

namespace request
{
  struct get_hashed
  {
    std::string key;
    typedef std::unique_ptr<get_hashed> ptr;

    static get_hashed create_schema() 
    {
      get_hashed sch;
      sch.key = "key1";
      return sch;
    }
  };
}

namespace response
{
  struct get_hashed
  {
    size_t value = 0;
    bool status = false;
    typedef std::unique_ptr<get_hashed> ptr;
    typedef std::function< void(ptr)> handler;

    static get_hashed create_schema() 
    {
      get_hashed sch;
      sch.value = std::hash<std::string>()("value1");
      sch.status = true;
      return sch;
    }

  };
}

}
