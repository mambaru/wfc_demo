//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/module/module.hpp>

namespace demo{ namespace storage{

class storage_module
  : public ::wfc::module
{
  class impl;
public:
  storage_module();
};

}}

