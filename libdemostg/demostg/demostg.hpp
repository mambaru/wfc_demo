//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017-2018, 2022
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once 

#include <string>
#include <mutex>
#include <map>

class demostg
{
public:
  bool set(const std::string& key, const std::string& val);
  bool get(const std::string& key, std::string* val) const;
private:
  mutable std::mutex _mutex;
  std::map<std::string, std::string> _storage;
};
