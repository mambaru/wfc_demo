#pragma once

#include <memory>
#include <functional>

namespace demo{ namespace pingpong{
  
namespace request
{
  struct pong
  {
    int ping_count = 0;
    int pong_count = 0;

    typedef std::unique_ptr<pong> ptr;
  };
}

namespace response
{
  struct pong
  {
    int ping_count = 0;
    int pong_count = 0;

    typedef std::unique_ptr<pong> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
