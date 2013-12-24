#pragma once

#include "domain_config.hpp"

namespace wamba{ namespace demo{

struct domain_config_json
{
  typedef wfc::json::object<
    domain_config,
    fas::type_list_n<
    
    >::type
  > type;
  
  typedef type::serializer serializer; 
};

}}
