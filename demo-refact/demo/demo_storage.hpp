#pragma once

#include "idemo.hpp"
#include <hash/idemo_hash.hpp>
#include <unordered_map>
#include <mutex>

namespace wamba{ namespace demo{

class demo_storage
{
public:
  typedef std::string key_type;
  typedef std::string value_type;
  
  typedef std::unordered_map< key_type, data_type> storage_type;

  void set(const key_type& name,  const data_type& data);
  void set(key_type&& name,  data_type&& data);
  bool get(const key_type& name,  data_type& text);

private:
  std::unordered_map< key_type, data_type> _storage;
};

}}
