//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include "pinger_config.hpp"
#include <wfc/json.hpp>

namespace demo{ namespace pingpong{

struct pinger_config_json
{
  JSON_NAME(target_list)
  
  typedef ::wfc::json::object<
    pinger_config,
    wfc::json::member_list<
      wfc::json::member< n_target_list, pinger_config, std::vector<std::string>, &pinger_config::target_list,
        ::wfc::json::vector_of_strings<>
      >
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
