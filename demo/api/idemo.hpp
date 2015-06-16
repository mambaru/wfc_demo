#pragma once

#include <demo/api/set.hpp>
#include <demo/api/get.hpp>

#include <wfc/iinterface.hpp>
#include <memory>
#include <functional>

namespace wamba{ namespace demo{

struct idemo: public ::wfc::iinterface
{
  virtual ~idemo() {}
  virtual void set(request::set::ptr req, response::set::callback cb ) = 0;
  virtual void get(request::get::ptr req, response::get::callback cb ) = 0;
};



}}
