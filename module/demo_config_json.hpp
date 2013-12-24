#pragma once

#include <wfc/json/json.hpp>
#include <wfc/json/name.hpp>

#include "demo_config.hpp"
//#include "service/server_tcp_config_json.hpp"
#include <wfc/jsonrpc/server_tcp_config_json.hpp>
#include "domain/domain_config_json.hpp"

namespace wamba{ namespace demo{

struct demo_config_json
{
  FAS_NAME(enabled)
  FAS_NAME(tcp)
  
  typedef wfc::json::object<
    demo_config,
    fas::type_list_n<
      wfc::json::base<domain_config_json::type>,
      wfc::json::member<n_enabled, demo_config, bool,              &demo_config::enabled>,
      wfc::json::member<n_tcp,     demo_config, wfc::jsonrpc::server_tcp_config, &demo_config::tcp,     wfc::jsonrpc::server_tcp_config_json::type>
    >::type
  > type;
  
  typedef type::serializer serializer; 
};

}}
