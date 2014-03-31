#pragma once

#include <demo/idemo.hpp>
#include "api/generate_json.hpp"
#include "api/reverse_json.hpp"
#include "api/get_json.hpp"
#include "api/set_json.hpp"
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ namespace gateway{

typedef wfc::gateway::provider<idemo> provider_type;
JSONRPC_TAG(set)
JSONRPC_TAG(get)
JSONRPC_TAG(generate)
JSONRPC_TAG(reverse)
  
struct method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<idemo>,
  wfc::jsonrpc::provider< provider_type >,
  wfc::jsonrpc::interface_<idemo>,
  ::wfc::jsonrpc::shutdown< ::wfc::jsonrpc::mem_fun_shutdown< provider_type, &provider_type::shutdown> >,
  ::wfc::jsonrpc::startup< ::wfc::jsonrpc::mem_fun_startup< idemo, provider_type,  &provider_type::startup> >, 

  wfc::jsonrpc::dual_method< _set_,      request::set_json,      response::set_json,      idemo, &idemo::set>,
  wfc::jsonrpc::dual_method< _get_,      request::get_json,      response::get_json,      idemo, &idemo::get>,
  wfc::jsonrpc::dual_method< _generate_, request::generate_json, response::generate_json, idemo, &idemo::generate>,
  wfc::jsonrpc::dual_method< _reverse_,  request::reverse_json,  response::reverse_json,  idemo, &idemo::reverse>
>
{
  void set(set_request_ptr req, set_callback cb ) 
  {
    this->call<_set_>( std::move(req), cb, nullptr);
  }
  
  void get(get_request_ptr , get_callback  )
  {
    
  }
  
  void reverse(reverse_request_ptr , reverse_callback  )
  {
    
  }
  
  void generate(generate_request_ptr , generate_callback  )
  {
    
  }

};

}}}