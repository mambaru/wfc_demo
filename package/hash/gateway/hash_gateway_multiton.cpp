//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "hash_gateway_multiton.hpp"
#include "hash_gateway.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{ namespace hash{

WFC_NAME2(hash_gateway_name, "hash-gateway")

class hash_gateway_multiton::impl: public ::wfc::jsonrpc::gateway_multiton
< 
  hash_gateway_name, 
  gateway_method_list, 
  hash_interface 
> 
{};

hash_gateway_multiton::hash_gateway_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}}
