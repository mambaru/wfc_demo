//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2017
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/module/component.hpp>

namespace demo{ namespace pingpong{

class pinger_gateway_multiton
  : public ::wfc::component
{
public:
  pinger_gateway_multiton();
};

}}
