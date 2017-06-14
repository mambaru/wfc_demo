#pragma once

#include <storage/api/set.hpp>
#include <storage/api/get.hpp>
#include <storage/api/get_hash.hpp>
#include <wfc/iinterface.hpp>

namespace wamba{ namespace demo{ namespace storage{

struct istorage
  : public ::wfc::iinterface
{
  virtual ~istorage() {}
  virtual void set( request::set::ptr req, response::set::handler cb ) = 0;
  virtual void get( request::get::ptr req, response::get::handler cb ) = 0;
  virtual void get_hash( request::get_hash::ptr req, response::get_hash::handler cb ) = 0;
};

}}}
