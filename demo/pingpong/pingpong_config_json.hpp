//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include "pingpong_config.hpp"
#include <wfc/json.hpp>

namespace wamba{ namespace pingpong{

struct pingpong_config_json
{
  JSON_NAME(target_list)
  
  typedef ::wfc::json::object<
    pingpong_config,
    ::wfc::json::member_list<
      ::wfc::json::member< n_target_list, pingpong_config, std::vector<std::string>, &pingpong_config::target_list,
        ::wfc::json::array< std::vector< ::wfc::json::value<std::string> > >
      >
      /*
      ::wfc::json::member< n_repli_target, demo_config, std::string, &demo_config::repli_target>,
      ::wfc::json::member< n_hash_target, demo_config, std::string, &demo_config::hash_target>
      */
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
