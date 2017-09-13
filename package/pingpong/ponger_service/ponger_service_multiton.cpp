//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "ponger_service_multiton.hpp"
#include "ponger_service.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

#include <memory>

namespace demo{ namespace pingpong{

namespace
{
  WFC_NAME2(service_name, "ponger-service")

  class impl
    : public wfc::jsonrpc::service_multiton<service_name, service::ponger_method_list, service::pinger_interface>{};
}

ponger_service_multiton::ponger_service_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
