#pragma once

#include <string>
#include <set>
#include <map>
#include <memory>
#include <functional>

namespace demo{

namespace request
{
  struct multiget_hashed
  {
    std::set<std::string> keys;
    typedef std::unique_ptr<multiget_hashed> ptr;
    
    static multiget_hashed create_schema() 
    {
      multiget_hashed sch;
      sch.keys.insert("key1");
      sch.keys.insert("key2");
      sch.keys.insert("key3");
      return sch;
    }

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
    
    static multiget_hashed create_schema() 
    {
      multiget_hashed sch;
      std::hash<std::string> h;
      sch.values["key1"]=std::make_shared<size_t>(h("value1"));
      sch.values["key2"]=std::make_shared<size_t>(h("value2"));
      sch.values["key3"]=std::make_shared<size_t>(h("value3"));
      return sch;
    }

  };
}

}
