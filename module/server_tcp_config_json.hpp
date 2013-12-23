#pragma once

#include <wfc/jsonrpc/server_tcp_config_json.hpp>
#include <wfc/json/json.hpp>
#include "server_tcp_config.hpp"

namespace wamba{ namespace demo{

struct server_tcp_config_json
{
  typedef wfc::json::object<
    server_tcp_config,
    fas::type_list_n<
       wfc::json::base< wfc::jsonrpc::server_tcp_config_json::type>
    >::type
  > type;
  
  typedef type::serializer serializer; 
};

}}
