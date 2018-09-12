//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "pinger_multiton.hpp"
#include "pinger.hpp"
#include "pinger_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace demo{ namespace pingpong{

namespace
{
  WFC_NAME2(object_name, "pinger")

  class impl: public ::wfc::multiton<
    object_name,
    wfc::instance<pinger>,
    pinger_config_json, 
    wfc::component_features::IgnoreReconfigure
  >
  {  
  };
}

pinger_multiton::pinger_multiton()
  : component( std::make_shared<impl>() )
{
}

}}
