//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <demo/hash/hash_config.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{ namespace hash{

struct hash_config_json
{
  JSON_NAME(repli_target)
  JSON_NAME(hash_target)
  
  typedef ::wfc::json::object<
    hash_config,
    ::wfc::json::member_list<
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}}
