#pragma once

#include "api/hash.hpp"

#include <memory>
#include <functional>

namespace wamba{ namespace demo{

struct idemo_hash
{
  typedef std::unique_ptr<request::hash> hash_request_ptr;
  typedef std::unique_ptr<response::hash> hash_response_ptr;
  typedef std::function< void(hash_response_ptr)> hash_callback;

  virtual ~idemo_hash() {}
  
  virtual void hash(hash_request_ptr req, hash_callback cb ) = 0;
};

}}
