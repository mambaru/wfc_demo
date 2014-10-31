#pragma once

#include <demo/idemo.hpp>

#include "api/get_json.hpp"
#include "api/set_json.hpp"
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ namespace gateway{

typedef wfc::provider::provider<idemo> provider_type;
JSONRPC_TAG(set)
JSONRPC_TAG(get)
  
struct demo_api: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::dual_interface<idemo, provider_type>,
  wfc::jsonrpc::dual_method< _set_,      request::set_json,      response::set_json,      idemo, &idemo::set>,
  wfc::jsonrpc::dual_method< _get_,      request::get_json,      response::get_json,      idemo, &idemo::get>
>
{
  virtual void set(idemo::set_request_ptr req, idemo::set_callback cb ) 
  {
    this->call<_set_>( std::move(req), cb, nullptr );
  }
  
  virtual void get(idemo::get_request_ptr req, idemo::get_callback cb )
  {
    this->call<_get_>( std::move(req), cb, nullptr );
  }
};


class demo_client
  : public idemo 
{
public:
  typedef std::shared_ptr<provider_type> provider_ptr;
  
  demo_client(provider_ptr provider)
    : _provider(provider) {}
  
  virtual void set(set_request_ptr req, set_callback cb )
  {
    _provider->post(&idemo::set, std::move(req), std::move(cb));
  }
  
  virtual void get(get_request_ptr req, get_callback cb )
  {
    _provider->post(&idemo::get, std::move(req), std::move(cb));
  }

private:
  provider_ptr _provider;
};

}}}
