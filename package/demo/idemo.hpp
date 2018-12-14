#pragma once

#include <demo/api/set.hpp>
#include <demo/api/get.hpp>
#include <demo/api/get_hashed.hpp>
#include <demo/api/multiget.hpp>
#include <demo/api/multiget_hashed.hpp>
#include <demo/api/multiget_hashed2.hpp>
#include <wfc/iinterface.hpp>

namespace demo{

struct istorage
  : public ::wfc::iinterface
{
  virtual ~istorage() {}
  virtual void set( request::set::ptr req, response::set::handler cb ) = 0;
  virtual void get( request::get::ptr req, response::get::handler cb ) = 0;
  virtual void multiget( request::multiget::ptr req, response::multiget::handler cb ) = 0;
  virtual void get_hashed( request::get_hashed::ptr req, response::get_hashed::handler cb ) = 0;
  virtual void multiget_hashed( request::multiget_hashed::ptr , response::multiget_hashed::handler  ) = 0;
  virtual void multiget_hashed2( request::multiget_hashed2::ptr , response::multiget_hashed2::handler  ) = 0;
};

}
