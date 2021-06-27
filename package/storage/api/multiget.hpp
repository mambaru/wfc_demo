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

    static multiget create_schema()
    {
      multiget sch;
      sch.keys.insert("key1");
      sch.keys.insert("key2");
      sch.keys.insert("key3");
      return sch;
    }
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

    static multiget create_schema()
    {
      multiget sch;
      sch.values["key1"]=std::make_shared<std::string>("value1");
      sch.values["key2"]=std::make_shared<std::string>("value2");
      sch.values["key3"]=std::make_shared<std::string>("value3");
      return sch;
    }
  };
}

}}
