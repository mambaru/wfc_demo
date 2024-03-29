//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pinger_service_multiton.hpp"
#include "pinger_service.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

#include <memory>

namespace damba{ namespace pingpong{

namespace
{
  WFC_NAME2(service_name, "pinger-service")

  class impl
    : public wfc::jsonrpc::service_multiton<service_name, service::pinger_method_list, service::ponger_interface>{};
}

pinger_service_multiton::pinger_service_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
