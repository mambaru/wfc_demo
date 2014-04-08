#pragma once

#include <wfc/service/rn/jsonrpc/service_config_json.hpp>
#include <wfc/gateway/rn/jsonrpc/gateway_config_json.hpp>
#include <wfc/json/json.hpp>
#include <wfc/json/name.hpp>

#include "demo_config.hpp"
//#include <wfc/jsonrpc/server_tcp_config_json.hpp>
#include "domain/domain_config_json.hpp"

namespace wamba{ namespace demo{

struct demo_config_json
{
  JSON_NAME(enabled)
  JSON_NAME(is_proxy)
  JSON_NAME(services)
  JSON_NAME(gateways)
  
  
  typedef wfc::service::rn::jsonrpc::service_list_config service_list_config;
  typedef wfc::service::rn::jsonrpc::service_list_config_json service_list_config_json;

  typedef wfc::gateway::rn::jsonrpc::gateway_list_config gateway_list_config;
  typedef wfc::gateway::rn::jsonrpc::gateway_list_config_json gateway_list_config_json;

  typedef wfc::json::object<
    demo_config,
    fas::type_list_n<
      wfc::json::base<domain_config_json>,
      wfc::json::member<n_enabled,  demo_config, bool,              &demo_config::enabled>,
      wfc::json::member<n_services, demo_config, service_list_config, &demo_config::services, service_list_config_json>, 
      wfc::json::member<n_gateways, demo_config, gateway_list_config, &demo_config::gateways, gateway_list_config_json>
      >::type
  > type;
  typedef type::target target;
  typedef type::serializer serializer; 
};

}}
