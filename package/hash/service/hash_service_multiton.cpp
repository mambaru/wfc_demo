//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "hash_service_multiton.hpp"
#include "hash_service.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{ namespace hash{

WFC_NAME2(hash_service_name, "hash-service")

namespace 
{
  class impl
    : public ::wfc::jsonrpc::service_multiton< hash_service_name, service_method_list> 
  {};
  
}

hash_service_multiton::hash_service_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}}
