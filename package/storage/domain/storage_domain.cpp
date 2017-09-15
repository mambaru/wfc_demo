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
  if ( this->bad_request<response::set>(req, cb) )
    return;
  
  _storage.set(req->key, req->value);

  if (cb!=nullptr)
    cb( std::make_unique<response::set>() );
}

void storage_domain::get(request::get::ptr req, response::get::handler cb ) 
{
  if ( this->notify_ban<response::get>(req, cb) )
    return;

  auto res = std::make_unique<response::get>();
  res->status = _storage.get(req->key, res->value);
  cb( std::move(res) );
}

void storage_domain::multiget(request::multiget::ptr req, response::multiget::handler cb ) 
{
  if ( this->notify_ban<response::multiget>(req, cb) )
    return;

  auto res = std::make_unique<response::multiget>();
  std::shared_ptr<std::string> pval;
  for (const std::string& key : req->keys )
  {
    if ( pval == nullptr )
      pval = std::make_shared<std::string>();
    if ( _storage.get(key, *pval) )
      res->values[key] = std::move(pval);
    else
      res->values[key] = nullptr;
  }
  cb( std::move(res) );
}

void storage_domain::get_hashed( request::get_hashed::ptr req, response::get_hashed::handler cb ) 
{
  if ( this->notify_ban<response::get_hashed>(req, cb) )
    return;
  
  if ( _hash==nullptr )
    return cb(nullptr);
  
  std::string value;
  if ( _storage.get( req->key, value) )
  {
    using hash_request  = ::demo::hash::request::get_hash;
    using hash_response = ::demo::hash::response::get_hash;
    auto req_hash = std::make_unique< hash_request >();
    req_hash->value = value;
    _hash->get_hash( std::move(req_hash), this->callback([cb]( hash_response::ptr res_hash)
    {
      if ( res_hash!= nullptr )
      {
        auto res = std::make_unique<response::get_hashed>();
        res->status = true;
        res->value = res_hash->value;
        cb( std::move(res) );
      }
      else
      {
        cb( nullptr );
      }
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
  std::cout << "void storage_domain::multiget_hashed( request::multiget_hashed::ptr req, response::multiget_hashed::handler cb) " << std::endl;
  if ( this->notify_ban<response::multiget_hashed>(req, cb) )
    return;
  
  if ( _hash==nullptr )
    return cb(nullptr);
  
  typedef wrtstat::time_meter<std::chrono::microseconds> meter_type;
  auto mf = []( std::string key,  time_t , time_t value, size_t count){
    std::cout << key << ":"<< value << "-" << count << std::endl;
  };
  
  auto psize = std::make_shared<size_t>( req->keys.size() );
  auto presp = std::make_shared<response::multiget_hashed::ptr>();
  *presp = std::make_unique<response::multiget_hashed>();
  auto pmutex = std::make_shared<std::recursive_mutex>();
  for ( auto key : req->keys )
  {
    std::string value;
    if ( _storage.get(key, value) )
    {
      using hash_request  = ::demo::hash::request::get_hash;
      using hash_response = ::demo::hash::response::get_hash;

      auto req_hash = std::make_unique<hash_request>();
      req_hash->value = value;
      
      using namespace std::placeholders;
      auto m = std::make_shared<meter_type>( std::bind(mf, key, _1, _2, _3),  std::time(0), 1);
      std::cout << "--> " << key << std::endl;
      _hash->get_hash( std::move(req_hash), this->callback([key, pmutex, psize, presp, cb, m](hash_response::ptr res_hash)
      {
        std::cout << "<-- " << key << std::endl;
        std::lock_guard<std::recursive_mutex> lk(*pmutex);

        if ( *psize == 0 ) 
          return;
        
        *psize -= 1;
        
        if ( res_hash!=nullptr )
        {
          (*presp)->values[key] = std::make_shared<size_t>( res_hash->value );
          if ( *psize == 0 )
            cb( std::move(*presp) );
        }
        else
        {
          *psize = 0;
          cb( nullptr );
        }
      }));
    }
    else
    {
      std::lock_guard<std::recursive_mutex> lk(*pmutex);
      *psize -= 1;
      (*presp)->values[key] = nullptr;
    }
  }
  if ( *psize == 0 )
    cb( std::move(*presp) );
}

}}
