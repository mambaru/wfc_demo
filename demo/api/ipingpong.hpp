#pragma once

#include <demo/api/pingpong/ping.hpp>
#include <demo/api/pingpong/pong.hpp>
#include <wfc/iinterface.hpp>

namespace wamba{ namespace pingpong{

struct ipingpong: public ::wfc::iinterface
{
  virtual ~ipingpong() {}
  virtual void ping(request::ping::ptr, response::ping::handler, io_id_t, std::weak_ptr<ipingpong> ) = 0;
  virtual void pong(request::pong::ptr, response::pong::handler) = 0;

  typedef std::function<void(request::pong::ptr, response::pong::handler)> pong_handler;
  virtual void ping2(request::ping::ptr, response::ping::handler, io_id_t, pong_handler ) = 0;
  
  virtual void startup(io_id_t, std::weak_ptr<ipingpong> ) = 0;

};

}}
