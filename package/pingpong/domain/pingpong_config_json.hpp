//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include "pingpong_config.hpp"
#include <wfc/json.hpp>

namespace demo{ namespace pingpong{

struct pingpong_config_json
{
  JSON_NAME(target_list)
  JSON_NAME(stress_ping)
  JSON_NAME(deny_pong)
  
  typedef ::wfc::json::object<
    pingpong_config,
    ::wfc::json::member_list<
      ::wfc::json::member< n_deny_pong, pingpong_config, bool, &pingpong_config::deny_pong>,
      ::wfc::json::member< n_stress_ping, pingpong_config, size_t, &pingpong_config::stress_ping>,
      ::wfc::json::member< n_target_list, pingpong_config, std::vector<std::string>, &pingpong_config::target_list,
        ::wfc::json::array< std::vector< ::wfc::json::value<std::string> > >
      >
      
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
