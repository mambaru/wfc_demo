//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include "domain/demo_config.hpp"
#include <wfc/json.hpp>

namespace wamba{ namespace demo{

struct demo_config_json
{
  JSON_NAME(repli_target)
  JSON_NAME(hash_target)
  
  typedef ::wfc::json::object<
    demo_config,
    ::wfc::json::member_list<
      ::wfc::json::member< n_repli_target, demo_config, std::string, &demo_config::repli_target>,
      ::wfc::json::member< n_hash_target, demo_config, std::string, &demo_config::hash_target>
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
