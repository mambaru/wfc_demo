#pragma once


#include <wfc/module/multi_instance.hpp>
#include "demo_instance.hpp"
#include "demo_config_json.hpp"
#include "build_info.h"

namespace wamba{ namespace demo{

class demo_module
  : public wfc::multi_instance<demo_build_info, demo_config_json, demo_instance>
{
  
};

}}