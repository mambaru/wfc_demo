//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include <demostg/demostg.hpp>
#include "demo_config.hpp"
#include <demo/idemo.hpp>
#include <hash/ihash.hpp>
#include <memory>
#include <string>
#include <map>

namespace damba{ namespace demo{

class demo_domain
  : public ::wfc::domain_object<idemo, demo_config>
{
  typedef hash::ihash ihash;
public:
  virtual void initialize() override;
  virtual void set(request::set::ptr req, response::set::handler cb ) override;
  virtual void get(request::get::ptr req, response::get::handler cb ) override;
  virtual void multiget( request::multiget::ptr , response::multiget::handler  ) override;
  virtual void get_hashed( request::get_hashed::ptr req, response::get_hashed::handler cb ) override;
  virtual void multiget_hashed( request::multiget_hashed::ptr , response::multiget_hashed::handler  ) override;
  virtual void multiget_hashed2( request::multiget_hashed2::ptr , response::multiget_hashed2::handler  ) override;
private:
  std::shared_ptr<ihash> _hash;
  demostg _demo;
};

}}
