#pragma once

#include <memory>
#include <functional>

namespace damba{ namespace pingpong{

  struct ball
  {
    size_t count = 0;
    size_t power = 0;
    typedef std::unique_ptr<ball> ptr;
    typedef std::function< void(ptr)> handler;
  };

}}
