#pragma once

namespace wamba{ namespace pingpong{

namespace request
{
  struct ping
  {
    int ping_count = 0;
    int pong_count = 0;
    typedef std::unique_ptr<ping> ptr;
  };
}

namespace response
{
  struct ping
  {
    int ping_count = 0;
    int pong_count = 0;
    typedef std::unique_ptr<ping> ptr;
    typedef std::function< void(ptr)> handler;
  };
}

}}
