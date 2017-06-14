//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "storage.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>

namespace demo{ namespace storage{

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

void storage::get_hashed( request::get_hashed::ptr req, response::get_hashed::handler cb ) 
{
  if ( this->notify_ban<response::get_hashed>(req, cb) )
    return;
  
  if ( _hash==nullptr )
    return cb(nullptr);
  
  std::unique_lock< mutex_type > lk(_mutex);
  auto itr = _storage.find( req->key );
  if ( itr != _storage.end() )
  {
    using hash_request  = ::demo::hash::request::get_hash;
    using hash_response = ::demo::hash::response::get_hash;
    auto req_hash = std::make_unique< hash_request >();
    req_hash->value = itr->second;
    _hash->get_hash( std::move(req_hash), [cb]( hash_response::ptr res_hash)
    {
      auto res = std::make_unique<response::get_hashed>();
      res->status = true;
      res->value = res_hash->value;
      cb( std::move(res) );
    });
  }
  else
  {
    lk.unlock();
    auto res = std::make_unique<response::get_hashed>();
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
  if ( itr != _storage.end() )
  {
    res->status = true;
    res->value = itr->second;
  }
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

}}
