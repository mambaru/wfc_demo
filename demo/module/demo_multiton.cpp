//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "demo_multiton.hpp"
#include "../demo/demo.hpp"
#include "../demo/demo_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(demo_object_name, "demo")

class demo_multiton_impl: public ::wfc::multiton<
  demo_object_name,
  wfc::instance<demo_domain>,
  demo_config_json
>
{  
};

demo_multiton::demo_multiton()
  : component( std::make_shared<demo_multiton_impl>() )
{
}

}}
