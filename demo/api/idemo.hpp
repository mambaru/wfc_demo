#pragma once

#include <demo/api/demo/set.hpp>
#include <demo/api/demo/get.hpp>
#include <wfc/iinterface.hpp>

namespace wamba{ namespace demo{

struct idemo
  : public ::wfc::iinterface
{
  virtual ~idemo() {}
  virtual void set(request::set::ptr req, response::set::handler cb ) = 0;
  virtual void get(request::get::ptr req, response::get::handler cb ) = 0;
};

}}
