//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include "ponger_config.hpp"
#include <pingpong/iponger.hpp>
#include <memory>
#include <string>


namespace damba{ namespace pingpong{

class ponger
  : public ::wfc::domain_object< iponger, ponger_config>
{
  typedef std::vector< std::weak_ptr<iponger> > target_list;
public:
  virtual void reconfigure() override;
  virtual void ping(ball::ptr, ball::handler, io_id_t, std::weak_ptr<ipinger> ) override;
private:
  std::atomic<size_t> _pong_count;
};

}}
