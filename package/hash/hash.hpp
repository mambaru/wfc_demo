//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include <hash/hash_config.hpp>
#include <hash/ihash.hpp>

namespace wamba{ namespace demo{ namespace hash{

class hash
  : public ::wfc::domain_object<ihash, hash_config>
{
public:
  virtual void get_hash( request::get_hash::ptr req, response::get_hash::handler cb ) override;
};

}}}