#pragma once

#include "idemo_hash.hpp"

namespace wamba{ namespace demo{

class demo_hash
  : public idemo_hash
{
public:
  virtual ~demo_hash();
  virtual void hash(hash_request_ptr req, hash_callback cb );
};

}}
