//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include "demo_config.hpp"
#include <demo/api/idemo.hpp>
#include <memory>
#include <string>


namespace wamba{ namespace demo{

class demo_writer;

class demo_domain
  : public ::wfc::domain_object<idemo, demo_config>
  , public std::enable_shared_from_this<demo_domain>
{
public:
  virtual void reconfigure() override;
  virtual void set(request::set::ptr req, response::set::handler cb ) override;
  virtual void get(request::get::ptr req, response::get::handler cb ) override;
  virtual void perform_io(data_ptr /*d*/, io_id_t /*io_id*/, outgoing_handler_t handler) override;
private:
  std::shared_ptr<idemo> _reply;
};

}}
