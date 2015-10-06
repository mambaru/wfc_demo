//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_module.hpp"
#include "demo_multiton.hpp"
#include "demo_service_multiton.hpp"
#include "demo_gateway_multiton.hpp"
//#include "pingpong_multiton.hpp"
//#include "pingpong_service_multiton.hpp"
//#include "pingpong_gateway_multiton.hpp"
#include <wfc/module/component_list.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(demo_module_name, "demo")

class demo_module::impl: public ::wfc::component_list<
  demo_module_name,
  demo_multiton,
  demo_service_multiton,
  demo_gateway_multiton
>
{
};

demo_module::demo_module()
  : module( std::make_shared<demo_module::impl>() )
{
}

}}
