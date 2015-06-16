#pragma once

#include "api/hash_json.hpp"
#include <hash/idemo_hash.hpp>
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ namespace service{

JSONRPC_TAG(hash)

namespace wjr = ::wfc::jsonrpc;
  
struct hash_api
  : wjr::method_list
    <
      wjr::target<idemo_hash>,
      wjr::invoke_method< _hash_, request::hash_json, response::hash_json, idemo_hash, &idemo_hash::hash>
    >
{
};

}}}
