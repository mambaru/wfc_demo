// TODO: #include <wfc/module.hpp>
#include <wfc/module/multi_instance.hpp>
#include "hash_instance.hpp"
#include "hash_module.hpp"
#include <wfc/module/imodule.hpp>
#include "hash_build_info.h"

namespace wamba{ namespace demo{ namespace hash_module_impl{  

typedef wfc::service::rn::jsonrpc::service_list_config_json hash_config_json;

class module_impl
  : public ::wfc::multi_instance<hash_build_info, hash_config_json, hash_instance>
{
  
};


#include <wfc/module/module_impl.inl>

}}}


/*
#include <wfc/module/multi_instance.hpp>
#include "hash_instance.hpp"
#include "hash_build_info.h"

namespace wamba{ namespace demo{

typedef wfc::service::rn::jsonrpc::service_list_config_json hash_config_json;

class hash_module
  : public wfc::multi_instance<hash_build_info, hash_config_json, hash_instance>
{
  
};

}}
*/