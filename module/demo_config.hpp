#pragma once

//#include "service/server_tcp_config.hpp"
//#include <wfc/jsonrpc/server_tcp_config.hpp>
#include "domain/domain_config.hpp"
#include <wfc/service.hpp>

namespace wamba{ namespace demo{

struct demo_config
  : domain_config
{
  bool enabled = true;
  bool proxy_mode = false;
  wfc::service::rn::jsonrpc::service_list_config services;
  wfc::gateway::rn::jsonrpc::gateway_list_config gateways;
};

}}
