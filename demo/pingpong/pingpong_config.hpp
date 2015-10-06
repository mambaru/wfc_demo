//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace wamba{ namespace pingpong{

struct pingpong_config
{
  std::vector<std::string> target_list;
  bool deny_pong = false;
  int stress_ping = 0;
};

}}
