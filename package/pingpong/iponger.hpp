#pragma once

#include <pingpong/api/ball.hpp>
#include <pingpong/ipinger.hpp>

#include <wfc/iinterface.hpp>

namespace demo{ namespace pingpong{


struct iponger: public ::wfc::iinterface
{
  virtual ~iponger() {}
  virtual void ping(ball::ptr, ball::handler, io_id_t, std::weak_ptr<ipinger> ) = 0;
};

}}
