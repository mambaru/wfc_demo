#include "demostg.hpp"

bool demostg::set(const std::string& key, const std::string& val)
{
  std::lock_guard<std::mutex> lk(_mutex);
  return _storage.emplace(key,val).second;
}

bool demostg::get(const std::string& key, std::string* val) const
{
  std::lock_guard<std::mutex> lk(_mutex);
  auto itr = _storage.find(key);
  if ( itr == _storage.end() )
    return false;
  if ( val!=nullptr )
    *val = itr->second;
  return true;
}

  
