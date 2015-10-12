//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong_module.hpp"
#include "pingpong_multiton.hpp"
#include "pingpong_service_multiton.hpp"
#include "pingpong_gateway_multiton.hpp"
#include <wfc/module/component_list.hpp>
#include <wfc/name.hpp>
#include <memory>

namespace wamba{ namespace pingpong{

WFC_NAME2(pingpong_module_name, "pingpong")

class pingpong_module::impl: public ::wfc::component_list<
  pingpong_module_name,
  pingpong_multiton,
  pingpong_service_multiton,
  pingpong_gateway_multiton
>
{
};

pingpong_module::pingpong_module()
  : module( std::make_shared<impl>() )
{
}

}}