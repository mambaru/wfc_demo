//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_module.hpp"
#include "demo_object.hpp"
#include <wfc/module/object_list.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(demo_module_name, "demo")

class demo_module_impl: public ::wfc::object_list<
  demo_module_name,
  demo_object
>
{
};

demo_module::demo_module()
  : module( std::make_shared<demo_module_impl>() )
{
}

}}
