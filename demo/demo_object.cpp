//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_object.hpp"
#include "domain/demo_domain.hpp"
#include "demo_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(demo_object_name, "demo")

class demo_object_impl: public ::wfc::multiton<
  demo_object_name,
  wfc::instance<demo_domain>,
  demo_config_json
>
{  
};

demo_object::demo_object()
  : object( std::make_shared<demo_object_impl>() )
{
}

}}
