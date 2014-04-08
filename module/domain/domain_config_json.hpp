#pragma once

#include "domain_config.hpp"
#include <wfc/json/json.hpp>
#include <wfc/json/name.hpp>

namespace wamba{ namespace demo{

struct domain_config_json
{
  FAS_NAME(generate_threads)
  JSON_NAME(is_proxy)
  
  typedef wfc::json::object<
    domain_config,
    fas::type_list_n<
      wfc::json::member<n_is_proxy, domain_config, bool,              &domain_config::is_proxy>,
      wfc::json::member< n_generate_threads, domain_config, size_t, &domain_config::generate_threads>
    >::type
  > type;
  
  typedef type::target target;
  typedef type::member_list member_list; 
  typedef type::serializer serializer; 
};

}}
