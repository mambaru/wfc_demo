//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/module/component.hpp>

namespace wamba{ namespace demo{

class demo_multiton
  : public ::wfc::component
{
  class impl;
public:
  demo_multiton();
};

}}