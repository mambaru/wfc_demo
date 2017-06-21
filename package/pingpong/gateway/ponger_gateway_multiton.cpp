//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "ponger_gateway_multiton.hpp"
#include "ponger_gateway.hpp"


#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace demo{ namespace pingpong{

namespace 
{
  WFC_NAME2(gateway_name, "ponger-gateway")

  class impl:
    public ::wfc::jsonrpc::gateway_multiton<
      gateway_name, 
      gateway::ponger_method_list, 
      gateway::ponger_interface
    >
  {
  public:
    virtual std::string interface_name() override
    {
      return "iponger";
    }

    virtual std::string description() override
    {
      return "ponger description";
    }
  };
}

ponger_gateway_multiton::ponger_gateway_multiton()
  : wfc::component( std::make_shared<impl>() )
{
}

}}
