#pragma once

#include <pingpong/api/ping.hpp>
#include <pingpong/api/pong.hpp>
#include <wfc/iinterface.hpp>

namespace demo{ namespace pingpong{

struct ipingpong: public ::wfc::iinterface
{
  typedef std::function<void(request::pong::ptr, response::pong::handler)> pong_handler;

  virtual ~ipingpong() {}

  virtual void ping(request::ping::ptr, response::ping::handler, io_id_t, std::weak_ptr<ipingpong> ) = 0;
  virtual void ping2(request::ping::ptr, response::ping::handler, io_id_t, pong_handler ) = 0;

  virtual void pong(request::pong::ptr, response::pong::handler) = 0;
  virtual void startup(io_id_t, std::weak_ptr<ipingpong> ) = 0;
};

struct ipinger: public ::wfc::iinterface
{
  typedef std::function<void(request::ping::ptr, response::ping::handler)> ping_handler;
  
  virtual ~ipinger() {}
  virtual void ping(request::ping::ptr, response::ping::handler) = 0;
  virtual void pong(request::pong::ptr, response::pong::handler, io_id_t, ping_handler ) = 0;
};

struct iponger: public ::wfc::iinterface
{
  virtual ~ipinger() {}
  virtual void ping(request::ping::ptr, response::ping::handler, io_id_t, std::weak_ptr<ipinger> ) = 0;
};

}}
