#pragma once

#include <demo/storage/api/set.hpp>
#include <demo/storage/api/get.hpp>
#include <wfc/iinterface.hpp>

namespace wamba{ namespace demo{ namespace storage{

struct istorage
  : public ::wfc::iinterface
{
  virtual ~istorage() {}
  virtual void set( request::set::ptr req, response::set::handler cb ) = 0;
  virtual void get( request::get::ptr req, response::get::handler cb ) = 0;
};

}}}
