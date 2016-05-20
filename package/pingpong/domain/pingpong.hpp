//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include "pingpong_config.hpp"
#include <pingpong/ipingpong.hpp>
#include <memory>
#include <string>


namespace wamba{ namespace pingpong{


class pingpong
  : public ::wfc::domain_object< ipingpong, pingpong_config>
  , public std::enable_shared_from_this<pingpong>
{
  
public:
  virtual void reconfigure() override;
  virtual void ping(request::ping::ptr req, response::ping::handler cb, io_id_t, std::weak_ptr<ipingpong> ) override;
  virtual void ping2(request::ping::ptr, response::ping::handler, io_id_t, pong_handler ) override;
  virtual void pong(request::pong::ptr req, response::pong::handler cb ) override;
  virtual void reg_io(io_id_t io_id, std::weak_ptr<iinterface> ) override;
  virtual void startup(io_id_t, std::weak_ptr<ipingpong> ) override;

private:
  
  typedef std::mutex mutex_type;
  
  response::ping::handler make_response_wrapper_(/*size_t size,*/ response::ping::handler cb, ipingpong::pong_handler pong_reqester);

  void reping_(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, pong_handler handler);
  void stress_ping_();
  void stress_result_( response::ping::ptr, std::chrono::high_resolution_clock::time_point );
  void stat_( time_t ms, size_t pingc, size_t pongc );

  typedef std::shared_ptr<ipingpong> pingpong_ptr;
  typedef std::list<pingpong_ptr> pingpong_list;
  pingpong_list _targets;
  std::atomic<bool> _deny_pong;
  std::atomic<size_t> _stress_ping;
  std::atomic<bool> _stress_flag;
  std::vector<time_t> _intervals;
  mutable mutex_type _mutex;
  std::atomic<time_t> _show_time;
  std::atomic<size_t> _stat_count;
  std::chrono::high_resolution_clock::time_point _stat_time;
};

}}
