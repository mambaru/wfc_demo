//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_build_info.h"
#include "demo_package.hpp"
#include "storage/storage_module.hpp"
#include "module/pingpong_module.hpp"
#include <wfc/module/module_list.hpp>
#include <wfc/name.hpp>

namespace wamba{

WFC_NAME2(demo_package_name, "demo")

class demo_package::impl: public ::wfc::module_list<
  demo_build_info,
  demo::storage::storage_module,
  pingpong::pingpong_module
>
{
};

demo_package::demo_package()
  : package( std::make_shared<demo_package::impl>() )
{
}

}
