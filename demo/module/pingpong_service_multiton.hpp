//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/module/object.hpp>

namespace wamba{ namespace demo{

class pingpong_service_multiton
  : public ::wfc::object
{
public:
  pingpong_service_multiton();
};

}}
