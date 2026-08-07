#pragma once

#include <memory>
#include <functional>

namespace damba{ namespace pingpong{

  struct ball
  {
    int64_t count = 0;
    int64_t power = 0;
    typedef std::unique_ptr<ball> ptr;
    typedef std::function< void(ptr)> handler;
  };

}}
