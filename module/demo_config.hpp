#pragma once

//#include "service/server_tcp_config.hpp"
#include <wfc/jsonrpc/server_tcp_config.hpp>
#include "domain/domain_config.hpp"

namespace wamba{ namespace demo{

struct demo_config
  : domain_config
{
  bool enabled;
  //server_tcp_config tcp;
  wfc::jsonrpc::server_tcp_config tcp;
  demo_config()
    : enabled(true)
    , tcp()
  {}
};

}}
