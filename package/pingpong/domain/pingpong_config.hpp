//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace demo{ namespace pingpong{

struct pingpong_config
{
  std::vector<std::string> target_list;
  bool deny_pong = false;
  size_t stress_ping = 0;
};

}}
