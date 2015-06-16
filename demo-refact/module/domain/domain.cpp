#include <wfc/memory.hpp>
#include <wfc/io/io_base.hpp>
//#include <wfc/jsonrpc/errors/error.hpp>
#include <memory>
#include "domain.hpp"

#include <iostream>

namespace wamba{ namespace demo{

 
domain::~domain()
{
  
}

domain::domain( const domain_config& conf, std::shared_ptr<provider_type> provider)
  : _provider( provider )
{
  this->reconfigure(conf);
}

void domain::reconfigure(const domain_config& conf)
{
  //std::lock_guard<mutex_type> lk(_mutex);
  _conf = conf;
}

void domain::start()
{
}

void domain::set( request::set::ptr, response::set::callback)
{
  /*
  std::lock_guard<mutex_type> lk(_mutex);
  auto cli = _provider->get();
  if ( _demo==nullptr && cli==nullptr )
  {
    return cb(nullptr);
  }
  
  idemo::set_request_ptr req_cpy = nullptr;
  if ( cli!=nullptr && _demo!= nullptr )
  {
    req_cpy = std::make_unique<request::set>(*req);
  }

 
  if ( _demo!=nullptr )
  {
    _demo->set( std::move(req), cb);
    if ( cli!=nullptr )
      req = std::move(req_cpy);
  }
  
  //std::cout << "data size " << req->data.size() << std::endl;
  
  if ( cli!=nullptr )
  {
    if ( _demo!=nullptr )
    {
      _provider->post( &idemo::set, std::move(req), idemo::set_callback(nullptr) );
    }
    else
    {
      cli->set( std::move(req), cb);
    }
  }
  */

}

void domain::get( request::get::ptr, response::get::callback)
{
  /*
  std::lock_guard<mutex_type> lk(_mutex);
  
  if ( _demo != nullptr )
  {
    _demo->get( std::move(req), cb);
  }
  else if (auto cli = _provider->get() )
  {
    cli->get( std::move(req), cb);
  }
  */
}


}}
