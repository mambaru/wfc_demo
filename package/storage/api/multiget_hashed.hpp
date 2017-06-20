#pragma once

#include <string>
#include <set>
#include <map>
#include <memory>
#include <functional>

namespace demo{ namespace storage{  

namespace request
{
  struct multiget_hashed
  {
    std::set<std::string> keys;
    typedef std::unique_ptr<multiget_hashed> ptr;
  };
}

namespace response
{
  struct multiget_hashed
  {
    typedef std::map<std::string, std::shared_ptr<size_t> > map_type;
    map_type values;
    typedef std::unique_ptr<multiget_hashed> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
