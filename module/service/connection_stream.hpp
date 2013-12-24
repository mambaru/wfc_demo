#pragma once

#include <wfc/jsonrpc/connection_stream.hpp>

#include "api/method_list.hpp"
#include "context.hpp"

namespace wamba{ namespace demo{

struct connection_stream
  : wfc::jsonrpc::connection_stream<
      method_list,
      wfc::jsonrpc::context< context >
    > 
{};
  
}}
