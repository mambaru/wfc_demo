//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong_module.hpp"
#include "domain/pingpong_multiton.hpp"
#include "tank/tank_multiton.hpp"
#include "service/pingpong_service_multiton.hpp"
#include "gateway/pingpong_gateway_multiton.hpp"
#include <wfc/module/component_list.hpp>
#include <wfc/name.hpp>
#include <memory>

namespace demo{ namespace pingpong{

namespace {
  WFC_NAME2(module_name, "pingpong")

  class impl: public ::wfc::component_list<
    module_name,
    pingpong_multiton,
    tank_multiton,
    pingpong_service_multiton,
    pingpong_gateway_multiton
  >
  {
  };
}

pingpong_module::pingpong_module()
  : module( std::make_shared<impl>() )
{
}

}}
