//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/module/component.hpp>

namespace damba{ namespace pingpong{

class tank_multiton
  : public ::wfc::component
{
public:
  tank_multiton();
};

}}
