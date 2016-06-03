//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include "tank_config.hpp"
#include <wfc/domain_object.hpp>
#include <memory>
#include <string>


namespace wamba{ namespace pingpong{


class tank
  : public ::wfc::domain_object< ::wfc::iinterface, tank_config>
  , public std::enable_shared_from_this<tank>
{
  
public:
  // domain_object
  virtual void ready() override;
private:
};

}}
