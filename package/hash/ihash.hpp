#pragma once

#include <hash/api/get_hash.hpp>
#include <wfc/iinterface.hpp>

namespace demo{ namespace hash{

struct ihash
  : public ::wfc::iinterface
{
  virtual ~ihash() {}
  virtual void get_hash( request::get_hash::ptr req, response::get_hash::handler cb ) = 0;
};

}}
