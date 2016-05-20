//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//
#pragma once

#include <storage/storage_config.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace demo{ namespace storage{

struct storage_config_json
{
  JSON_NAME(repli_target)
  JSON_NAME(hash_target)
  
  typedef ::wfc::json::object<
    storage_config,
    ::wfc::json::member_list<
      ::wfc::json::member< n_repli_target, storage_config, std::string, &storage_config::repli_target>,
      ::wfc::json::member< n_hash_target, storage_config, std::string, &storage_config::hash_target>
    >
  > type;

  typedef type::serializer serializer;
  typedef type::target target;
  typedef type::member_list member_list;
};

}}}
