#pragma once 

#include <string>
#include <mutex>
#include <map>

class storage
{
public:
  void set(std::string key, std::string val);
  bool get(std::string key, std::string& val) const;
private:
  mutable std::mutex _mutex;
  std::map<std::string, std::string> _storage;
};
