//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include "ponger_config.hpp"
#include <wfc/json.hpp>

namespace demo{ namespace pingpong{

struct ponger_config_json
{
  JSON_NAME(pong_count)
  
  typedef ::wfc::json::object<
    ponger_config,
    wfc::json::member_list<
      wfc::json::member< n_pong_count, ponger_config, size_t, &ponger_config::pong_count>
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
