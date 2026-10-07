//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2015-2017, 2022
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace damba{ namespace pingpong{

struct pinger_config
{
  std::vector<std::string> target_list;
};

}}
