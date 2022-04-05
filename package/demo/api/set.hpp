#pragma once

#include <string>
#include <memory>
#include <functional>

namespace damba{ namespace demo{

namespace request
{
  struct set
  {
    std::string key;
    std::string value;
    typedef std::unique_ptr<set> ptr;

    static bool create_schema(set& g, const std::string& name)
    {
      if ( name.empty() ) g.key = "empty1";
      else if ( name == "example_request" || name == "example2") g.key = "example2";
      else g.key = "unknown1";
      g.value = name;
      return true;
    }

    static std::vector<std::string> get_schema_list() { return {"example_request", "example2"}; }
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

}}
