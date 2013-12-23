#pragma once

#include "server_tcp_config.hpp"

namespace wamba{ namespace demo{

struct demo_config
{
  bool enabled;
  server_tcp_config tcp;
  demo_config()
    : enabled(true)
    , tcp()
  {}
};

}}
