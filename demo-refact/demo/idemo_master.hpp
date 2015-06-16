#pragma once

#include "idemo.hpp"
#include "api/restore.hpp"

#include <memory>
#include <functional>

namespace wamba{ namespace demo{

struct idemo_slave;
struct idemo_master: idemo
{
  typedef std::unique_ptr<request::restore> restore_request_ptr;
  typedef std::unique_ptr<response::restore> restore_response_ptr;
  typedef std::function< void(restore_response_ptr)> restore_callback;
  typedef std::shared_ptr<idemo_slave> idemo_slave_ptr;

  virtual void restore_to(restore_request_ptr req, restore_callback cb, size_t client_id, idemo_slave_ptr dst) = 0;
  virtual void restore_cancel(size_t client_id) = 0;
};

}}
