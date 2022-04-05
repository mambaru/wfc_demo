#pragma once

#include <hash/ihash.hpp>
#include <hash/api/get_hash_json.hpp>
#include <wfc/jsonrpc.hpp>

namespace damba{ namespace hash {

JSONRPC_TAG(get_hash)

struct service_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<ihash>,
  wfc::jsonrpc::invoke_method< _get_hash_, request::get_hash_json, response::get_hash_json, ihash, &ihash::get_hash>
>
{
};

}}
