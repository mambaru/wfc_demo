//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include "tank_config.hpp"
#include <pingpong/ipinger.hpp>
#include <wfc/domain_object.hpp>
#include <wrtstat/wrtstat.hpp>
#include <memory>
#include <string>


namespace demo{ namespace pingpong{


class tank
  : public ::wfc::domain_object< ::wfc::iinterface, tank_config>
  //, public std::enable_shared_from_this<tank>
{
  typedef std::chrono::high_resolution_clock clock_t;
public:
  // domain_object
  virtual void start() override;
  virtual void stop() override;
  virtual void reconfigure() override;
  virtual void initialize() override;
  //virtual void ready() override;
  void fire();
private:
 // void result_handler(clock_t::time_point tp, ball::ptr);
private:
  std::weak_ptr<ipinger> _target;
  std::thread _thread;
  std::atomic<size_t> _discharge;
  std::atomic<size_t> _power;
};

}}
