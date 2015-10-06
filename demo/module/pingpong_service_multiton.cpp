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

namespace wamba{ namespace pingpong{

WFC_NAME2(pingpong_service_name, "pingpong-service")

typedef ::wfc::jsonrpc::service_multiton<pingpong_service_name, pingpong::pingpong_method_list, pingpong::pingpong_interface> impl;

pingpong_service_multiton::pingpong_service_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
