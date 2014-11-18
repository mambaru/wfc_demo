#pragma once

#include <wfc/module/imodule.hpp>
namespace wamba{ namespace demo{

namespace demo_module_impl
{  
#include <wfc/module/module_decl.inl>
}

struct demo_module: demo_module_impl::module{};
  
}}

/*
#pragma once


#include <wfc/module/multi_instance.hpp>
#include "demo_instance.hpp"
#include "demo_config_json.hpp"
#include "demo_build_info.h"

namespace wamba{ namespace demo{

class demo_module
  : public wfc::multi_instance<demo_build_info, demo_config_json, demo_instance>
{
  
};

}}
*/