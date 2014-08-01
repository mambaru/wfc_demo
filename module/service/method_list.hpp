#pragma once

#include <demo/idemo.hpp>
#include "api/generate_json.hpp"
#include "api/reverse_json.hpp"
#include "api/get_json.hpp"
#include "api/set_json.hpp"
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ namespace service{

JSONRPC_TAG(push)
JSONRPC_TAG(set)
JSONRPC_TAG(get)
JSONRPC_TAG(generate)
JSONRPC_TAG(reverse)
  
/*
   ::wfc::jsonrpc::dual_method2<
    _subscribe_, 
    request::subscribe_json::type,
    response::subscribe_json::type,
    request::publish,
    response::publish,
    ipubsub, 
    &ipubsub::subscribe,
    ipubsub, 
    &ipubsub::publish
  >,
  */
struct method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::target<idemo>,
  //wfc::jsonrpc::interface_<idemo_callback>,
  wfc::jsonrpc::invoke_method< _set_,      request::set_json,      response::set_json,      idemo, &idemo::set>,
  wfc::jsonrpc::invoke_method< _get_,      request::get_json,      response::get_json,      idemo, &idemo::get>,
  wfc::jsonrpc::invoke_method< _reverse_,  request::reverse_json,  response::reverse_json,  idemo, &idemo::reverse>/*,
  wfc::jsonrpc::invoke_method2<
    _generate_, 
    request::generate_json::type, 
    response::generate_json::type, 
    idemo_callback::push_request, 
    idemo_callback::push_response,
    idemo, 
    &idemo::generate,
    idemo_callback,
    &idemo_callback::push
  >,
  wfc::jsonrpc::method<
    wfc::jsonrpc::name<_push_>,
    wfc::jsonrpc::call< response::generate_json, ::wfc::json::value<bool> >
  >*/
>
{
  virtual void push( idemo_callback::push_request_ptr /*req*/, idemo_callback::push_callback /*cb*/)
  {
    //this->call<_push_>( std::move(req), cb, nullptr);
  };
};

}}}
