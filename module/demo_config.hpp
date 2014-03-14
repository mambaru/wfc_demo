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
  wfc::service::rn::jsonrpc::configuration service;
  
  /*//wfc::jsonrpc::server_tcp_config tcp;
  
  demo_config()
    : domain_config()
    , enabled(true)
    //, tcp()
  {
  }
  */
  
};

}}
