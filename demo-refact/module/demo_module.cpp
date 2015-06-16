#include <wfc/module/multi_instance.hpp>
#include "demo_module.hpp"
#include "demo_instance.hpp"
#include "demo_config_json.hpp"
#include "demo_build_info.h"

namespace wamba{ namespace demo{

class demo_module_impl
  : public ::wfc::multi_instance<demo_build_info, demo_config_json, demo_instance>
{};

demo_module::demo_module()
  : ::wfc::module( std::make_shared<demo_module_impl>() )
{}

}}


/*
#include <wfc/module/multi_instance.hpp>
#include "demo_instance.hpp"
#include "demo_module.hpp"
#include "demo_config_json.hpp"
#include <wfc/module/imodule.hpp>
#include "demo_build_info.h"

namespace wamba{ namespace demo{ namespace demo_module_impl{  

typedef wfc::service::rn::jsonrpc::service_list_config_json hash_config_json;

class module_impl
  : public ::wfc::multi_instance<demo_build_info, demo_config_json, demo_instance>
{
  
};


#include <wfc/module/module_impl.inl>

}}}
*/