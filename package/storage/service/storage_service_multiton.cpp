//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "storage_service_multiton.hpp"
#include "storage_service.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{ namespace storage{

namespace
{
  WFC_NAME2(service_name, "storage-service")

  class impl
    : public ::wfc::jsonrpc::service_multiton< service_name, service_method_list> 
  {};
}

storage_service_multiton::storage_service_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}}
