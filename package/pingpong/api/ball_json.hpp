#pragma once

#include <pingpong/api/ball.hpp>
#include <wfc/json.hpp>

namespace damba{ namespace pingpong{

struct ball_json
{
  JSON_NAME(count)
  JSON_NAME(power)
  typedef wfc::json::object<
    ball,
    wfc::json::member_list<
      wfc::json::member<n_count, ball, size_t, &ball::count>,
      wfc::json::member<n_power, ball, size_t, &ball::power>
    >
  > type;

  typedef type::target     target;
  typedef type::serializer serializer;
};

}}
