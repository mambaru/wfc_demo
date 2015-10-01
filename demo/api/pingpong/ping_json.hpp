#pragma once

#include <demo/api/pingpong/ping.hpp>
#include <wfc/json.hpp>

namespace wamba{ namespace pingpong{

namespace request
{
  struct ping_json
  {
    JSON_NAME(ping)
    JSON_NAME(pong)

    typedef wfc::json::object<
      ping,
      wfc::json::member_list<
        wfc::json::member<n_ping, ping, int, &ping::ping_count>,
        wfc::json::member<n_pong, ping, int, &ping::pong_count>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

namespace response
{
  struct ping_json
  {
    JSON_NAME(ping)
    JSON_NAME(pong)

    typedef wfc::json::object<
      ping,
      wfc::json::member_list<
        wfc::json::member<n_ping, ping, int, &ping::ping_count>,
        wfc::json::member<n_pong, ping, int, &ping::pong_count>
      >
    > type;

    typedef type::target     target;
    typedef type::serializer serializer;
  };
}

}}
