//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2015-2017, 2022
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <hash/api/get_hash.hpp>
#include <wfc/iinterface.hpp>

namespace damba{ namespace hash{

struct ihash
  : public ::wfc::iinterface
{
  virtual ~ihash() {}
  virtual void get_hash( request::get_hash::ptr req, response::get_hash::handler cb ) = 0;
};

}}
