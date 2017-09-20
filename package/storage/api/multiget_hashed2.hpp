#pragma once

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <functional>

namespace demo{ namespace storage{  

namespace request
{
  struct multiget_hashed2
  {
    std::vector<std::string> keys;
    typedef std::unique_ptr<multiget_hashed2> ptr;
  };
}

namespace response
{
  struct multiget_hashed2
  {
    typedef std::pair<std::string, std::shared_ptr<size_t> > kv_pair;
    typedef std::vector< kv_pair > kv_list;
    kv_list values;
    typedef std::unique_ptr<multiget_hashed2> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
