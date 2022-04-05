//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "hash_module.hpp"
#include "domain/hash_multiton.hpp"
#include "service/hash_service_multiton.hpp"
#include "gateway/hash_gateway_multiton.hpp"
#include <wfc/module/component_list.hpp>
#include <wfc/name.hpp>

namespace damba{ namespace hash{

namespace
{
  WFC_NAME2(module_name, "hash-module")

  class impl: public ::wfc::component_list<
    module_name,
    hash_multiton,
    hash_service_multiton,
    hash_gateway_multiton
  >
  {
  public:
    virtual std::string description() const override
    {
      return "Demo-hash module description";
    }
  };
}

hash_module::hash_module()
  : module( std::make_shared<impl>() )
{
}

}}
