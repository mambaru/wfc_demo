#pragma once

#include <wfc/service/rn/jsonrpc/configuration_json.hpp>
#include <wfc/json/json.hpp>
#include <wfc/json/name.hpp>

#include "demo_config.hpp"
//#include <wfc/jsonrpc/server_tcp_config_json.hpp>
#include "domain/domain_config_json.hpp"

namespace wamba{ namespace demo{

struct demo_config_json
{
  FAS_NAME(enabled)
  FAS_NAME(service)
  
  typedef wfc::service::rn::jsonrpc::configuration service_config;
  typedef wfc::service::rn::jsonrpc::configuration_json service_config_json;
  
  typedef wfc::json::object<
    demo_config,
    fas::type_list_n<
      wfc::json::base<domain_config_json::type>,
      wfc::json::member<n_enabled, demo_config, bool,              &demo_config::enabled>,
      wfc::json::member<n_service, demo_config, service_config, &demo_config::service, service_config_json::type>
        //,
      //wfc::json::member<n_tcp,     demo_config, wfc::jsonrpc::server_tcp_config, &demo_config::tcp,     wfc::jsonrpc::server_tcp_config_json::type>
    >::type
  > type;
  
  typedef type::serializer serializer; 
};

}}
