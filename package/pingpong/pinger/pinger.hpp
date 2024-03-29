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


namespace damba{ namespace pingpong{

class pinger
  : public ::wfc::domain_object< ipinger, pinger_config>
  , public std::enable_shared_from_this<pinger>
{
  typedef wfc::domain_object< ipinger, pinger_config> super;
  typedef std::vector< std::weak_ptr<iponger2> > target_list;
public:
  virtual void initialize() override;
  virtual void play(ball::ptr, ball::handler) override;
  virtual void pong(ball::ptr, ball::handler, io_id_t, ball_handler ) override;
private:
  target_list get_target_list() const;
private:
  target_list _targets;
  mutable std::mutex _mutex;
};

}}
