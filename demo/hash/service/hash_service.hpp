#pragma once

#include <demo/hash/ihash.hpp>
#include <demo/hash/api/get_hash_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace wamba{ namespace demo{ namespace hash {

JSONRPC_TAG(hash)

struct service_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<ihash>,
  wfc::jsonrpc::invoke_method< _hash_,      request::get_hash_json,      response::get_hash_json,      ihash, &ihash::get_hash>
>
{
};

}}}
