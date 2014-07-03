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
  wfc::jsonrpc::dual_interface<idemo, provider_type>,
  wfc::jsonrpc::dual_method< _set_,      request::set_json,      response::set_json,      idemo, &idemo::set>,
  wfc::jsonrpc::dual_method< _get_,      request::get_json,      response::get_json,      idemo, &idemo::get>,
  wfc::jsonrpc::dual_method< _generate_, request::generate_json, response::generate_json, idemo, &idemo::generate>,
  wfc::jsonrpc::dual_method< _reverse_,  request::reverse_json,  response::reverse_json,  idemo, &idemo::reverse>
>
{
  virtual void set(set_request_ptr req, set_callback cb ) 
  {
    //std::cout << "########### method_list " << (cb!=nullptr) <<std::endl;
    if ( cb != nullptr )
    {
      this->call<_set_>( std::move(req), cb, [cb]( std::unique_ptr<wfc::jsonrpc::error> ) 
      {
        if ( cb!=nullptr )
          cb(nullptr);
      } );
    }
    else
    {
      this->call<_set_>( std::move(req), nullptr );
    }
  }
  
  virtual void get(get_request_ptr req, get_callback cb )
  {
    this->call<_get_>( std::move(req), cb, [cb]( std::unique_ptr<wfc::jsonrpc::error> ) 
    {
      if ( cb!=nullptr )
        cb(nullptr);
    });
  }
  
  virtual void reverse(reverse_request_ptr req, reverse_callback cb )
  {
    this->call<_reverse_>( std::move(req), cb, [cb]( std::unique_ptr<wfc::jsonrpc::error> ) 
    {
      if ( cb!=nullptr )
        cb(nullptr);
    });
  }
  
  virtual void generate(generate_request_ptr req, generate_callback cb )
  {
    this->call<_generate_>( std::move(req), cb, [cb]( std::unique_ptr<wfc::jsonrpc::error> ) 
    {
      if ( cb!=nullptr )
        cb(nullptr);
    });
  }
};

}}}
