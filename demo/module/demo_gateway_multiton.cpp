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

typedef ::wfc::jsonrpc::gateway_multiton<demo_gateway_name, demo_method_list, demo_interface > impl;

demo_gateway_multiton::demo_gateway_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
