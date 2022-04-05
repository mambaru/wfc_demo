//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include "hash_config.hpp"
#include <wfc/json.hpp>

namespace damba{ namespace hash{

struct hash_config_json
{
  JSON_NAME(param)
  typedef wfc::json::object<
    hash_config,
    wfc::json::member_list<
      wfc::json::member<n_param, hash_config, bool, &hash_config::param>
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
