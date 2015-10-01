//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_gateway_multiton.hpp"
#include "../gateway/demo_gateway.hpp"


#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(demo_gateway_name, "demo-gateway")

class demo_gateway_multiton_impl: public ::wfc::multiton<
  demo_gateway_name,
  wfc::instance<demo_gateway>,
  wfc::jsonrpc::jsonrpc_options_json< demo_gateway::options_type >
>
{
};

demo_gateway_multiton::demo_gateway_multiton()
  : wfc::object( std::make_shared<demo_gateway_multiton_impl>() )
{
}

}}
