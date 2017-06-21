//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include "pinger_config.hpp"
#include <pingpong/ipinger.hpp>
#include <pingpong/iponger.hpp>
#include <memory>
#include <string>


namespace demo{ namespace pingpong{

class pinger
  : public ::wfc::domain_object< ipinger, pinger_config>
  , public std::enable_shared_from_this<pinger>
{
  typedef std::vector< std::weak_ptr<iponger> > target_list;
public:
  virtual void initialize() override;
  virtual void play(ball::ptr, ball::handler) override;
  virtual void pong(ball::ptr, ball::handler, io_id_t, ball_handler ) override;
private:
  target_list get_target_list() const;
private:
  std::vector< std::weak_ptr<iponger> > _targets;
  mutable std::mutex _mutex;
};

}}
