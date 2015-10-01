//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong_gateway_multiton.hpp"
#include "../gateway/pingpong_gateway.hpp"


#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(pingpong_gateway_name, "pingpong-gateway")

class pingpong_gateway_multiton_impl: public ::wfc::multiton<
  pingpong_gateway_name,
  wfc::instance<pingpong::gateway>,
  wfc::jsonrpc::jsonrpc_options_json< pingpong::gateway::options_type >
>
{
};

pingpong_gateway_multiton::pingpong_gateway_multiton()
  : wfc::object( std::make_shared<pingpong_gateway_multiton_impl>() )
{
}

}}
