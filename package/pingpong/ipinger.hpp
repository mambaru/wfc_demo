#pragma once

#include <pingpong/api/ball.hpp>
#include <wfc/iinterface.hpp>

namespace damba{ namespace pingpong{

struct ipinger: public ::wfc::iinterface
{
  typedef std::function<void(ball::ptr, ball::handler)> ball_handler;
  
  virtual ~ipinger() {}
  virtual void play(ball::ptr, ball::handler) = 0;
  virtual void pong(ball::ptr, ball::handler, io_id_t, ball_handler ) = 0;
};

}}
