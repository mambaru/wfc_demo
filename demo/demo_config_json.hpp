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
  //using ::wfc::json::object;

  typedef ::wfc::json::object<
    demo_config,
    ::wfc::json::member_list<
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
