//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2015-2017, 2022
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
