#pragma once

#include "api/get.hpp"
#include "api/set.hpp"


#include <memory>
#include <functional>

namespace wamba{ namespace demo{



struct idemo
{
  virtual ~idemo() {}
  
  virtual void set(request::set::ptr req, response::set::callback cb ) = 0;
  virtual void get(request::get::ptr req, response::get::callback cb ) = 0;
};



}}
