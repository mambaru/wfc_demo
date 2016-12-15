//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "storage.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>

namespace wamba{ namespace demo{ namespace storage{

void storage::reconfigure()
{
  std::string repli_name = this->options().repli_target;
  std::string hash_name = this->options().hash_target;
  _reply = this->global()->registry.get<istorage>(repli_name);
  _hash = this->global()->registry.get<ihash>(hash_name);

  auto req = std::make_unique< ::wamba::demo::hash::request::get_hash >();
  req->value = "hello";

  if ( _hash!=nullptr )
  {
    _hash->get_hash( std::move(req), []( ::wamba::demo::hash::response::get_hash::ptr res )
    {
      if ( res != nullptr )
        std::cout << "reconfigure get_hash: " << res->value << std::endl;
      else
        std::cout << "reconfigure get_hash: " << "nullptr" << std::endl;
    });
  }
}

void storage::set(request::set::ptr req, response::set::handler cb )
{
  std::lock_guard< std::recursive_mutex > lk(_mutex);
  
  if ( req!=nullptr )
  {
    if ( _reply != nullptr )
    {
      _storage[req->key]=req->value;
    }
    else
    {
      _storage[ std::move(req->key) ]= std::move(req->value);
    }
  }

  if (cb!=nullptr)
  {
    auto resp = std::make_unique<response::set>();
    resp->status = (req!=nullptr);
    cb( std::move(resp));
    cb=nullptr;
  }

  if ( _reply != nullptr )
  {
    _reply->set( std::move(req), nullptr );
  }
}

void storage::get(request::get::ptr req, response::get::handler cb ) 
{
  std::lock_guard< std::recursive_mutex > lk(_mutex);
  
  if ( cb == nullptr )
    return;
  if ( req == nullptr )
    return cb( nullptr );

  auto res = std::make_unique<response::get>();
  auto itr = _storage.find( req->key );
  if ( itr == _storage.end() )
  {
    res->status = false;
  }
  else if ( _hash == nullptr )
  {
    res->status = true;
    res->value = itr->second;
  }
  else
  {
    typedef ::wamba::demo::hash::request::get_hash request_get_hash;
    typedef ::wamba::demo::hash::response::get_hash response_get_hash;

    std::weak_ptr<storage> wthis = this->shared_from_this();
    response_get_hash::handler get_hash_cb = this->callback([wthis,cb]( response_get_hash::ptr hash_res)
    {
      if ( auto pthis = wthis.lock() )
      {
        auto res = std::make_unique<response::get>();
        res->status = true;
        res->value = hash_res->value;
        cb( std::move( res ) );
      }
    });
    auto get_hash_req = std::make_unique<request_get_hash>();
    get_hash_req->value = itr->second;
    _hash->get_hash( std::move(get_hash_req), std::move(get_hash_cb) );
  }

  if (res!=nullptr)
    cb( std::move(res) );
}

void storage::perform_io(data_ptr d, io_id_t /*io_id*/, outgoing_handler_t handler)
{
  if (handler!=nullptr)
  {
    std::reverse(d->begin(), d->end());
    handler( std::move(d) );
    //handler( nullptr );
  }
}

}}}
