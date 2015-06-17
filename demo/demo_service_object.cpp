//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_service_object.hpp"
#include "service/method_list.hpp"
#include "demo_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(demo_service_object_name, "demo-service")

class demo_service_object_impl: public ::wfc::multiton<
  demo_service_object_name,
  wfc::instance<demo_service>,
  wfc::jsonrpc::jsonrpc_options_json< demo_service::options_type >
  /*wfc::json::object<
    demo_service::options_type,
    wfc::json::member_list<
    >
  >*/
>
{
};

demo_service_object::demo_service_object()
  : wfc::object( std::make_shared<demo_service_object_impl>() )
{
}

}}
