//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "hash_multiton.hpp"
#include "hash_config_json.hpp"
#include "hash.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{ namespace hash{

namespace
{
  WFC_NAME2(object_name, "hash")

  class impl: public ::wfc::multiton<
    object_name,
    ::wfc::instance<hash>,
    hash_config_json
  >
  {
    virtual std::string interface_name() override
    {
      return "ihash";
    }
  };
}

hash_multiton::hash_multiton()
  : component( std::make_shared<impl>() )
{
}

}}}
