//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <string>

namespace wamba{ namespace demo{ namespace storage{

struct storage_config
{
  std::string repli_target;
  std::string hash_target;
};

}}}