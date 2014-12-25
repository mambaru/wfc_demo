#include "demo_storage.hpp"

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
    return false;
  }
  data = itr->second;
  return true;
}

}}
