//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include <demo/storage/storage_config.hpp>
#include <demo/storage/istorage.hpp>
#include <demo/hash/ihash.hpp>
#include <memory>
#include <string>
#include <map>

namespace wamba{ namespace demo{ namespace storage{

class storage
  : public ::wfc::domain_object<istorage, storage_config>
  , public std::enable_shared_from_this<storage>
{
  typedef std::map<std::string, std::string> map_type;
  typedef ::wamba::demo::hash::ihash ihash;
public:
  virtual void reconfigure() override;
  virtual void set(request::set::ptr req, response::set::handler cb ) override;
  virtual void get(request::get::ptr req, response::get::handler cb ) override;
  virtual void perform_io(data_ptr d, io_id_t io_id, outgoing_handler_t handler) override;
private:
  std::shared_ptr<istorage> _reply;
  std::shared_ptr<ihash> _hash;
  map_type _storage;
  mutable std::recursive_mutex::mutex _mutex;
};

}}}
