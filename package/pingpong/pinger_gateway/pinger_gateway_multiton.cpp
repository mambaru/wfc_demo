//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2017
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pinger_gateway_multiton.hpp"
#include "pinger_gateway.hpp"


#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace demo{ namespace pingpong{

namespace 
{
  WFC_NAME2(gateway_name, "pinger-gateway")

  class impl:
    public ::wfc::jsonrpc::gateway_multiton<
      gateway_name, 
      gateway::pinger_method_list, 
      gateway::pinger_interface
    >
  {
  public:
    virtual std::string interface_name() const override
    {
      return "ipinger";
    }

    virtual std::string description() const override
    {
      return "pinger description";
    }
  };
}

pinger_gateway_multiton::pinger_gateway_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
