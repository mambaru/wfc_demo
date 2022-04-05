//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_gateway_multiton.hpp"
#include "demo_gateway.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace damba{ namespace demo{

WFC_NAME2(demo_gateway_name, "demo-gateway")

class demo_gateway_multiton::impl
  : public ::wfc::jsonrpc::gateway_multiton<
      demo_gateway_name,
      gateway_method_list,
      demo_interface
    >
{};

demo_gateway_multiton::demo_gateway_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
