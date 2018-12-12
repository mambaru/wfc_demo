#pragma once 

#include <string>
#include <mutex>
#include <map>

class storage
{
public:
  void set(const std::string& key, const std::string& val);
  bool get(const std::string& key, std::string& val) const;
private:
  mutable std::mutex _mutex;
  std::map<std::string, std::string> _storage;
};
