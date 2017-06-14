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
  std::string hash_name = this->options().hash_target;
  _hash = this->global()->registry.get<ihash>(hash_name);
}

void storage::set(request::set::ptr req, response::set::handler cb )
{
  if ( this->bad_request<response::set>(req, cb) )
    return;
  
  std::lock_guard< mutex_type > lk(_mutex);
  
  _storage[req->key]=req->value;

  if (cb!=nullptr)
    cb( std::make_unique<response::set>() );
}

void storage::get_hash( request::get_hash::ptr req, response::get_hash::handler cb ) 
{
  if ( this->notify_ban<response::get_hash>(req, cb) )
    return;
  
  std::unique_lock< mutex_type > lk(_mutex);
  auto itr = _storage.find( req->key );
  if ( itr != _storage.end() )
  {
    if ( _hash!=nullptr )
    {
      auto req_hash = std::make_unique< ::wamba::demo::hash::request::get_hash >();
      req_hash->value = itr->second;
      _hash->get_hash( std::move(req_hash), [cb](::wamba::demo::hash::response::get_hash::ptr res_hash)
      {
        auto res = std::make_unique<response::get_hash>();
        res->status = true;
        res->value = res_hash->value;
        cb( std::move(res) );
      });
    }
    else
    {
      cb(nullptr);
    }
  }
  else
  {
    lk.unlock();
    auto res = std::make_unique<response::get_hash>();
    res->status = false;
    cb( std::move(res) );
  }
}

void storage::get(request::get::ptr req, response::get::handler cb ) 
{
  if ( this->notify_ban<response::get>(req, cb) )
    return;

  std::lock_guard< mutex_type > lk(_mutex);
  

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
    if ( d!=nullptr )
      std::reverse(d->begin(), d->end());
    handler( std::move(d) );
  }
}

}}}
