//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong_service_multiton.hpp"
#include "../service/pingpong_service.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

#include <memory>

namespace wamba{ namespace demo{

WFC_NAME2(pingpong_service_name, "pingpong-service")

class pingpong_service_multiton_impl: public ::wfc::multiton<
  pingpong_service_name,
  wfc::instance< pingpong::pingpong_service>,
  wfc::jsonrpc::jsonrpc_options_json< pingpong::pingpong_service::options_type >
>
{
};

pingpong_service_multiton::pingpong_service_multiton()
  : wfc::object( std::make_shared<pingpong_service_multiton_impl>() )
{
}

}}
