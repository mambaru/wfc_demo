#pragma once

#include <storage/api/set.hpp>
#include <storage/api/get.hpp>
#include <storage/api/get_hashed.hpp>
#include <storage/api/multiget.hpp>
#include <storage/api/multiget_hashed.hpp>
#include <wfc/iinterface.hpp>

namespace demo{ namespace storage{

struct istorage
  : public ::wfc::iinterface
{
  virtual ~istorage() {}
  virtual void set( request::set::ptr req, response::set::handler cb ) = 0;
  virtual void get( request::get::ptr req, response::get::handler cb ) = 0;
  virtual void multiget( request::multiget::ptr req, response::multiget::handler cb ) = 0;
  virtual void get_hashed( request::get_hashed::ptr req, response::get_hashed::handler cb ) = 0;
  virtual void multiget_hashed( request::multiget_hashed::ptr , response::multiget_hashed::handler  ) = 0;
};

}}
