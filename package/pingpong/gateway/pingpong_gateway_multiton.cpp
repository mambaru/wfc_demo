//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong_gateway_multiton.hpp"
#include "../gateway/pingpong_gateway.hpp"


#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace demo{ namespace pingpong{

WFC_NAME2(pingpong_gateway_name, "pingpong-gateway")

class pingpong_gateway_multiton::impl:
  public ::wfc::jsonrpc::gateway_multiton<
    pingpong_gateway_name, 
    gateway::gateway_method_list, 
    gateway::pingpong_interface
  >
{
public:
  virtual std::string interface_name() override
  {
    return "ipingpong";
  }

  virtual std::string description() override
  {
    return "pingpong description";
  }
};

pingpong_gateway_multiton::pingpong_gateway_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
