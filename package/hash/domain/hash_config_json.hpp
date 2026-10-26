//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013, 2015-2018, 2022, 2026
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include "hash_config.hpp"
#include <wfc/json.hpp>

namespace damba{ namespace hash{

struct hash_config_json
{
  JSON_NAME(delay_ms)
  typedef wfc::json::object<
    hash_config,
    wfc::json::member_list<
      wfc::json::member<n_delay_ms, hash_config, int, &hash_config::delay_ms>
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}
