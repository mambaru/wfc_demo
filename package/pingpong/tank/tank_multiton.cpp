//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "tank_multiton.hpp"
#include "tank.hpp"
#include "tank_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace pingpong{

namespace {

  WFC_NAME2(object_name, "pingpong-tank")

  class impl: public ::wfc::multiton<
    object_name,
    wfc::instance<tank>,
    tank_config_json
  >
  {};
}

tank_multiton::tank_multiton()
  : component( std::make_shared<impl>() )
{
}

}}
