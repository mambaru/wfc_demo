//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2016
//
// Copyright: See COPYING file that comes with this distribution
//

#include "tank.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>
#include <atomic>
#include <memory>
#include <chrono>
#include <iomanip>


#define PINGPONG_LOG_MESSAGE(message) WFC_LOG_MESSAGE("pingpong", message)
#define PINGPONG_LOG_DEBUG(message)   WFC_LOG_DEBUG("pingpong", message)

namespace demo{ namespace pingpong{

void tank::ready()
{
}


}}
