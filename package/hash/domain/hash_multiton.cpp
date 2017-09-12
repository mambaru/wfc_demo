//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "hash_multiton.hpp"
#include "hash_config_json.hpp"
#include "hash_domain.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace demo{ namespace hash{

namespace
{
  WFC_NAME2(object_name, "hash")

  class impl: public ::wfc::multiton<
    object_name,
    ::wfc::instance<hash_domain>,
    hash_config_json,
      ::wfc::component_features::DisabledWorkflow
    | ::wfc::component_features::DisabledPriority
  >
  {
    virtual std::string interface_name() const override
    {
      return "ihash";
    }
  };
}

hash_multiton::hash_multiton()
  : component( std::make_shared<impl>() )
{
}

}}
