#pragma once

#include <cstddef>

namespace wamba{ namespace demo{

struct domain_config
{
  size_t generate_threads = 0;
  bool is_proxy = false;
};

}}
