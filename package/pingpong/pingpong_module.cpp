//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong_module.hpp"
#include "pinger/pinger_multiton.hpp"
#include "ponger/ponger_multiton.hpp"
#include "tank/tank_multiton.hpp"
#include "ponger_service/ponger_service_multiton.hpp"
#include "pinger_service/pinger_service_multiton.hpp"
#include "ponger_gateway/ponger_gateway_multiton.hpp"
#include "pinger_gateway/pinger_gateway_multiton.hpp"
#include <wfc/module/component_list.hpp>
#include <wfc/name.hpp>
#include <memory>

namespace demo{ namespace pingpong{

namespace {
  WFC_NAME2(module_name, "pingpong")

  class impl: public ::wfc::component_list<
    module_name,
    pinger_service_multiton,
    pinger_multiton,
    pinger_gateway_multiton,
    
    ponger_service_multiton,
    ponger_multiton,
    ponger_gateway_multiton,
    
    tank_multiton
  >
  {
  };
}

pingpong_module::pingpong_module()
  : module( std::make_shared<impl>() )
{
}

}}
