//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/module/component.hpp>

namespace wamba{ namespace demo{ namespace storage{

class storage_service_multiton
  : public ::wfc::component
{
public:
  storage_service_multiton();
};

}}}
