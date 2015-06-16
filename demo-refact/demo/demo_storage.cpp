#include "demo_storage.hpp"

#include <iostream>
namespace wamba{ namespace demo{


void demo_storage::set(const key_type& name,  const data_type& data)
{
  _storage[ name ] = data;
}

void demo_storage::set(key_type&& name,  data_type&& data)
{
  _storage[ name ] = data;
}

bool demo_storage::get(const key_type& name,  data_type& data)
{
  auto itr = _storage.find(name);
  if (itr == _storage.end() )
  {
    data.clear();
    return false;
  }
  std::cout << "-------------------" << std::endl;
  std::cout << data << std::endl;
  data = itr->second;
  return true;
}

}}
