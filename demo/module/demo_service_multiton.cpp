//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_service_multiton.hpp"
#include "../service/demo_service.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(demo_service_name, "demo-service")

class demo_service_multiton_impl: public ::wfc::multiton<
  demo_service_name,
  wfc::instance<demo_service>,
  wfc::jsonrpc::jsonrpc_options_json< demo_service::options_type >
>
{
};

demo_service_multiton::demo_service_multiton()
  : wfc::component( std::make_shared<demo_service_multiton_impl>() )
{
}

}}
