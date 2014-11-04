#pragma once

#include "idemo_master.hpp"

#include <memory>
#include <functional>

namespace wamba{ namespace demo{

struct idemo_slave: idemo
{
  typedef std::shared_ptr<idemo_master> idemo_masetr_ptr;

  virtual void restore_from(idemo_ptr dst) = 0;
  virtual void restore_stop() = 0;
};

}}
