//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace demo{ namespace storage{

struct storage_config
{
  std::string hash_target;

  static storage_config create_schema(const std::string& schema)
  {
    return storage_config{schema};
  }

  static std::vector<std::string> get_schema_list(){
    return {"example1", "example2"};
  }
};

}}
