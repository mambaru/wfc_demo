//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "storage_module.hpp"
#include "domain/storage_multiton.hpp"
#include "service/storage_service_multiton.hpp"
#include "gateway/storage_gateway_multiton.hpp"
#include <wfc/module/component_list.hpp>
#include <wfc/name.hpp>

namespace demo{ namespace storage{

WFC_NAME2(storage_module_name, "demo-storage")

class storage_module::impl: public ::wfc::component_list<
  storage_module_name,
  storage_multiton,
  storage_service_multiton,
  storage_gateway_multiton
>
{
  virtual std::string description() const override
  {
    return "Demo-storage module description";
  }
};

storage_module::storage_module()
  : module( std::make_shared<storage_module::impl>() )
{
}

}}
