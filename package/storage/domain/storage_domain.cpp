//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "storage_domain.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <wrtstat/wrtstat.hpp>
#include <iostream>
#include <functional>

namespace demo{ namespace storage{

void storage_domain::initialize()
{
  std::string hash_name = this->options().hash_target;
  _hash = this->get_target<ihash>(hash_name);
}

void storage_domain::set(request::set::ptr req, response::set::handler cb )
{
  if ( this->bad_request(req, cb) )
    return;

  auto res = this->create_response(cb);

  bool status =  _storage.set(req->key, req->value);
  if ( res!=nullptr )
    res->status = status;

  this->send_response( std::move(res), std::move(cb) );
}

void storage_domain::get(request::get::ptr req, response::get::handler cb )
{
  if ( this->notify_ban(req, cb) )
    return;

  auto res = std::make_unique<response::get>();
  res->status = _storage.get(req->key, &res->value);
  cb( std::move(res) );
}

void storage_domain::multiget(request::multiget::ptr req, response::multiget::handler cb )
{
  if ( this->notify_ban(req, cb) )
    return;

  auto res = std::make_unique<response::multiget>();
  std::shared_ptr<std::string> pval;
  for (const std::string& key : req->keys )
  {
    if ( pval == nullptr )
      pval = std::make_shared<std::string>();
    if ( _storage.get(key, &*pval) )
      res->values[key] = std::move(pval);
    else
      res->values[key] = nullptr;
  }
  cb( std::move(res) );
}

void storage_domain::get_hashed( request::get_hashed::ptr req, response::get_hashed::handler cb )
{
  if ( this->notify_ban(req, cb) )
    return;

  if ( _hash == nullptr )
    return cb(nullptr);

  std::string value;
  if ( _storage.get( req->key, &value) )
  {
    typedef ::demo::hash::request::get_hash  hash_request;
    typedef ::demo::hash::response::get_hash hash_response;
    auto req_hash = std::make_unique< hash_request >();
    req_hash->value = value;
    _hash->get_hash( std::move(req_hash), this->callback([cb]( hash_response::ptr res_hash)
    {
      if ( res_hash == nullptr )
      {
        cb( nullptr );
        return;
      }

      auto res = std::make_unique<response::get_hashed>();
      res->status = true;
      res->value = res_hash->value;
      cb( std::move(res) );
    }));
  }
  else
  {
    auto res = std::make_unique<response::get_hashed>();
    res->status = false;
    cb( std::move(res) );
  }
}

void storage_domain::multiget_hashed( request::multiget_hashed::ptr req, response::multiget_hashed::handler cb)
{
  if ( this->notify_ban(req, cb) )
    return;

  if ( _hash==nullptr )
    return cb(nullptr);

  auto presp = std::make_shared<response::multiget_hashed::ptr>();
  *presp = std::make_unique<response::multiget_hashed>();
  typedef ::demo::hash::request::get_hash hash_request;
  typedef std::unique_ptr<hash_request> hash_request_ptr;
  std::map<std::string, hash_request_ptr> hash_request_list;
  std::string value;
  for ( auto key : req->keys )
  {
    if ( _storage.get(key, &value) )
    {
      hash_request_list[key] = std::make_unique<hash_request>();
      hash_request_list[key]->value = value;
    }
    else
      (*presp)->values[key] = nullptr;
  }

  if ( hash_request_list.empty() )
    cb( std::move(*presp) );

  auto psize = std::make_shared<size_t>( hash_request_list.size() );
  auto pmutex = std::make_shared<std::recursive_mutex>();

  for (auto& req_hash: hash_request_list)
  {
    std::string key = req_hash.first;
    typedef  ::demo::hash::response::get_hash hash_response;
    _hash->get_hash( std::move(req_hash.second), this->callback([key, pmutex, psize, presp, cb](hash_response::ptr res_hash) mutable
    {
      std::unique_lock<std::recursive_mutex> lk(*pmutex);

      auto& ref_size = *psize;

      if ( ref_size == 0 )
        return;

      --(ref_size);

      if ( res_hash!=nullptr )
      {
        (*presp)->values[key] = std::make_shared<size_t>( res_hash->value );
        if ( ref_size == 0 )
        {
          cb( std::move(*presp) );
        }
      }
      else
      {
        ref_size = 0;
        cb( nullptr );
      }
    }));
  }
}

void storage_domain::multiget_hashed2( request::multiget_hashed2::ptr req, response::multiget_hashed2::handler cb)
{
  if ( this->notify_ban(req, cb) )
    return;

  if ( _hash==nullptr )
    return cb(nullptr);

  auto presp = std::make_shared<response::multiget_hashed2::ptr>();
  *presp = std::make_unique<response::multiget_hashed2>();
  typedef ::demo::hash::request::get_hash hash_request;
  typedef std::unique_ptr<hash_request> hash_request_ptr;
  std::vector< std::pair< std::string, hash_request_ptr > > hash_request_list;
  hash_request_list.reserve( req->keys.size() );
  std::string value;
  for ( auto key : req->keys )
  {
    if ( _storage.get(key, &value) )
    {
      hash_request_list.push_back( std::make_pair(key, std::make_unique<hash_request>() ) );
      hash_request_list.back().second->value = value;
      /*hash_request_list[key] = std::make_unique<hash_request>();
      hash_request_list[key]->value = value;*/
    }
    else
      (*presp)->values.push_back(std::make_pair(key, nullptr) );
  }

  if ( hash_request_list.empty() )
    cb( std::move(*presp) );

  auto psize = std::make_shared<size_t>( hash_request_list.size() );
  auto pmutex = std::make_shared<std::recursive_mutex>();

  for (auto& req_hash: hash_request_list)
  {
    std::string key = req_hash.first;
    typedef  ::demo::hash::response::get_hash hash_response;
    _hash->get_hash( std::move(req_hash.second), this->callback([key, pmutex, psize, presp, cb](hash_response::ptr res_hash) mutable
    {
      std::unique_lock<std::recursive_mutex> lk(*pmutex);
      auto& ref_size = *psize;

      if ( ref_size == 0 )
        return;

      --ref_size;

      if ( res_hash!=nullptr )
      {
        (*presp)->values.push_back(std::make_pair(key, std::make_shared<size_t>( res_hash->value ) ) );
        if ( ref_size == 0 )
        {
          cb( std::move(*presp) );
        }
      }
      else
      {
        ref_size = 0;
        cb( nullptr );
      }
    }));
  }
}

}}
