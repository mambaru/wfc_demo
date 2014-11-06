#pragma once

//#include "idemo_master.hpp"

#include <memory>
#include <functional>

namespace wamba{ namespace demo{

struct idemo_master;
struct idemo_slave: idemo
{
  typedef std::shared_ptr<idemo_master> idemo_master_ptr;

  virtual void restore_from(idemo_master_ptr dst) = 0;
  virtual void begin_restore();
  virtual void end_restore();
  virtual void restore_stop() = 0;
};

}}
