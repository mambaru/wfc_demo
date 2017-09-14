#pragma once

#include <string>
#include <set>
#include <map>
#include <memory>
#include <functional>

namespace demo{ namespace storage{  

namespace request
{
  struct multiget
  {
    std::set<std::string> keys;
    typedef std::unique_ptr<multiget> ptr;
  };
}

namespace response
{
  struct multiget
  {
    typedef std::map<std::string, std::shared_ptr<std::string> > map_type;
    map_type values;
    typedef std::unique_ptr<multiget> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
