//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/module/module.hpp>

namespace wamba{ namespace demo{ namespace hash{

class hash_module
  : public ::wfc::module
{
  class impl;
public:
  hash_module();
};

}}}
