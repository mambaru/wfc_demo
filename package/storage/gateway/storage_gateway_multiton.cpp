//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "storage_gateway_multiton.hpp"
#include "storage_gateway.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{ namespace storage{

WFC_NAME2(storage_gateway_name, "storage-gateway")

class storage_gateway_multiton::impl
  : public ::wfc::jsonrpc::gateway_multiton< 
      storage_gateway_name, 
      gateway_method_list, 
      storage_interface 
    > 
{};

storage_gateway_multiton::storage_gateway_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}}
