//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/module/component.hpp>

namespace demo{ namespace pingpong{

class pingpong_service_multiton
  : public ::wfc::component
{
public:
  pingpong_service_multiton();
};

}}
