//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include "tank_config.hpp"
#include <wfc/json.hpp>

namespace demo{ namespace pingpong{

struct tank_config_json
{
  JSON_NAME(discharge)
  
  typedef ::wfc::json::object<
    tank_config,
    ::wfc::json::member_list<
      ::wfc::json::member< n_discharge, tank_config, size_t, &tank_config::discharge>
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
