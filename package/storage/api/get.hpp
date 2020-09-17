#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace demo{ namespace storage{

namespace request
{
  struct get
  {
    std::string key;
    typedef std::unique_ptr<get> ptr;

    static bool create_schema(get& g, const std::string& name)
    {
      if ( name.empty() ) g.key = "empty1";
      else if ( name == "example_request" || name == "example1") g.key = "example1";
      else g.key = "unknown1";
      return true;
    }

    static std::vector<std::string> get_schema_list() { return {"example_request", "example1"}; }
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

    static get create_schema()
    {
      get sch;
      sch.value = "value1";
      sch.status = true;
      return sch;
    }
    static std::vector<std::string> get_schema_list() { return {"example_response"}; }

  };
}

}}
