#include "hash_build_info.h"

#include "hash_module.hpp"
#include "hash_instance.hpp"

#include <wfc/module/multi_instance.hpp>

namespace wamba{ namespace demo{

  typedef wfc::service::rn::jsonrpc::service_list_config_json hash_config_json;
  
class hash_module_impl
  : public ::wfc::multi_instance<hash_build_info, hash_config_json, hash_instance>
{};

hash_module::hash_module()
  : ::wfc::module( std::make_shared<hash_module_impl>() )
{}

}}


/*
#include <wfc/module/multi_instance.hpp>
#include "hash_instance.hpp"
#include "hash_build_info.h"

namespace wamba{ namespace demo{



class hash_module
  : public wfc::multi_instance<hash_build_info, hash_config_json, hash_instance>
{
  
};

}}
*/