//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017, 2022, 2024
//
// Copyright: See COPYING file that comes with this distribution
//

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
