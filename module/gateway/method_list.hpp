#pragma once

#include <demo/idemo.hpp>
#include <hash/idemo_hash.hpp>

#include "api/get_json.hpp"
#include "api/set_json.hpp"
#include "api/hash_json.hpp"
#include <wfc/jsonrpc.hpp>


namespace wamba{ namespace demo{ 

  /*
struct demo_gateway_config
{
  provider;
  jsonrpc;
  gateway;
};

  
struct gateway_config
{
  demo;
  hash;
};
*/
  
namespace gateway{

typedef wfc::provider::provider<idemo> demo_provider;
typedef wfc::provider::provider<idemo_hash> hash_provider;

JSONRPC_TAG(set)
JSONRPC_TAG(get)
JSONRPC_TAG(hash)
  
struct demo_api: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::dual_interface<idemo, demo_provider>,
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


struct hash_api: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::dual_interface<idemo_hash, hash_provider>,
  wfc::jsonrpc::dual_method< _hash_,      request::hash_json,      response::hash_json, idemo_hash, &idemo_hash::hash>
>
{
  virtual void hash(idemo_hash::hash_request_ptr req, idemo_hash::hash_callback cb ) 
  {
    this->call<_hash_>( std::move(req), cb, nullptr );
  }
};

class demo_proxy
  : public idemo 
{
public:
  typedef std::shared_ptr<demo_provider> provider_ptr;
  
  demo_proxy(provider_ptr provider)
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

class hash_proxy
  : public idemo_hash
{
public:
  typedef std::shared_ptr<hash_provider> provider_ptr;
  
  hash_proxy(provider_ptr provider)
    : _provider(provider) {}
  
  virtual void hash(hash_request_ptr req, hash_callback cb )
  {
    _provider->post(&idemo_hash::hash, std::move(req), std::move(cb));
  }
  

private:
  provider_ptr _provider;
};

}}}
