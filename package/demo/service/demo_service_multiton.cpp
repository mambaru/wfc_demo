//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_service_multiton.hpp"
#include "demo_service.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace damba{ namespace demo{

namespace
{
  WFC_NAME2(service_name, "demo-service")

  class impl
    : public ::wfc::jsonrpc::service_multiton< service_name, service_method_list>
  {};
}

demo_service_multiton::demo_service_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
