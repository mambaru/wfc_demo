#include "storage.hpp"

void storage::set(std::string key, std::string val)
{
  std::lock_guard<std::mutex> lk(_mutex);
  _storage[key]=val;
}

bool storage::get(std::string key, std::string& val) const
{
  val.clear();
  std::lock_guard<std::mutex> lk(_mutex);
  auto itr = _storage.find(key);
  if ( itr == _storage.end() )
    return false;
  val = itr->second;
  return true;
}

  
