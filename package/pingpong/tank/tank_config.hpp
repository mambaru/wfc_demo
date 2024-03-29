//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace damba{ namespace pingpong{

struct tank_config
{
  size_t power = 1;
  long discharge = 1;
  std::string target;
};

}}
