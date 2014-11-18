#pragma once

#include <wfc/module/imodule.hpp>
#include <sstream>

namespace wamba{ namespace demo{

namespace demo_module_impl
{  
#include <wfc/module/module_decl.inl>
}

class demo_module: public demo_module_impl::module
{
public:
                      
  virtual std::string description() const override
  {
    std::stringstream ss;
    ss << "Demo module. Options:" << std::endl
       << "\ttest=Time";
    return ss.str();
  }
};
  
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