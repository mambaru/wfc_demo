//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_module.hpp"
#include "domain/demo_multiton.hpp"
#include "service/demo_service_multiton.hpp"
#include "gateway/demo_gateway_multiton.hpp"
#include <wfc/module/component_list.hpp>
#include <wfc/name.hpp>

namespace damba{ namespace demo{

namespace
{
  WFC_NAME2(demo_module_name, "demo-module")

  class impl:
    public wfc::component_list<
      demo_module_name,
      demo_multiton,
      demo_service_multiton,
      demo_gateway_multiton
    >
  {
    virtual std::string description() const override
    {
      return "Demo-demo module description";
    }
  };
}

demo_module::demo_module()
  : module( std::make_shared<impl>() )
{
}

}}
