//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015, 2022
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_build_info.h"
#include "demo_package.hpp"
#include "demo/demo_module.hpp"
#include "hash/hash_module.hpp"
#include "pingpong/pingpong_module.hpp"

#include <wfc/module/module_list.hpp>

namespace damba{

namespace
{
  class impl: public wfc::module_list<
    demo_build_info,
    demo::demo_module,
    hash::hash_module,
    pingpong::pingpong_module
  >
  {};
}

demo_package::demo_package()
  : wfc::package( std::make_shared<impl>() )
{
}

}
