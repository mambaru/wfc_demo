//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include "storage_config.hpp"
#include <storage/istorage.hpp>
#include <storage/storage.hpp>
#include <hash/ihash.hpp>
#include <memory>
#include <string>
#include <map>

namespace demo{ namespace storage{

class storage_domain
  : public ::wfc::domain_object<istorage, storage_config>
{
  typedef ::demo::hash::ihash ihash;
public:
  virtual void reconfigure() override;
  virtual void set(request::set::ptr req, response::set::handler cb ) override;
  virtual void get(request::get::ptr req, response::get::handler cb ) override;
  virtual void get_hashed( request::get_hashed::ptr req, response::get_hashed::handler cb ) override;
  //virtual void perform_io(data_ptr d, io_id_t io_id, outgoing_handler_t handler) override;
private:
  std::shared_ptr<ihash> _hash;
  ::storage _storage;
};

}}
