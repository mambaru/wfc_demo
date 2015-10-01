//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include "pingpong_config.hpp"
#include <demo/api/ipingpong.hpp>
#include <memory>
#include <string>


namespace wamba{ namespace pingpong{


class pingpong
  : public ::wfc::domain_object< ipingpong, pingpong_config>
  , public std::enable_shared_from_this<pingpong>
{
public:
  virtual void reconfigure() override;
  virtual void ping(request::ping::ptr req, response::ping::handler cb, io_id_t, std::shared_ptr<ipingpong> ) override;
  virtual void pong(request::pong::ptr req, response::pong::handler cb ) override;
private:
  typedef std::shared_ptr<ipingpong> pingpong_ptr;
  typedef std::list<pingpong_ptr> pingpong_list;
  pingpong_list _targets;
};

}}
