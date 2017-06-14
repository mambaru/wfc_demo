#pragma once

#include <pingpong/api/pong.hpp>
#include <wfc/json.hpp>

namespace demo{ namespace pingpong{

namespace request
{
  struct pong_json
  {
    JSON_NAME(ping)
    JSON_NAME(pong)

    typedef wfc::json::object<
      pong,
      wfc::json::member_list<
        wfc::json::member<n_ping, pong, int, &pong::ping_count>,
        wfc::json::member<n_pong, pong, int, &pong::pong_count>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  struct pong_json
  {
    JSON_NAME(ping)
    JSON_NAME(pong)

    typedef wfc::json::object<
      pong,
      wfc::json::member_list<
        wfc::json::member<n_ping, pong, int, &pong::ping_count>,
        wfc::json::member<n_pong, pong, int, &pong::pong_count>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}
