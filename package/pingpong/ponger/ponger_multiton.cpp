//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "ponger_multiton.hpp"
#include "ponger.hpp"
#include "ponger_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace demo{ namespace pingpong{

namespace
{
  WFC_NAME2(object_name, "ponger")

  class impl: public ::wfc::multiton<
    object_name,
    wfc::instance<ponger>,
    ponger_config_json
  >
  {  
  };
}

ponger_multiton::ponger_multiton()
  : component( std::make_shared<impl>() )
{
}

}}
