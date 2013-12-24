#pragma once

#include "api/get.hpp"
#include "api/set.hpp"
#include "api/reverse.hpp"
#include "api/generate.hpp"

#include <memory>
#include <functional>

namespace wamba{ namespace demo{


struct idemo
{
  typedef std::unique_ptr<request::set> set_request_ptr;
  typedef std::unique_ptr<response::set> set_response_ptr;
  typedef std::function< void(set_response_ptr)> set_callback;

  typedef std::unique_ptr<request::get> get_request_ptr;
  typedef std::unique_ptr<response::get> get_response_ptr;
  typedef std::function< void(get_response_ptr)> get_callback;

  typedef std::unique_ptr<request::reverse> reverse_request_ptr;
  typedef std::unique_ptr<response::reverse> reverse_response_ptr;
  typedef std::function< void(reverse_response_ptr)> reverse_callback;

  typedef std::unique_ptr<request::generate> generate_request_ptr;
  typedef std::unique_ptr<response::generate> generate_response_ptr;
  typedef std::function<void(generate_response_ptr)> generate_callback;
  
  virtual ~idemo() {}
  
  virtual void set(set_request_ptr req, set_callback cb ) = 0;
  virtual void get(get_request_ptr req, get_callback cb ) = 0;
  virtual void reverse(reverse_request_ptr req, reverse_callback cb ) = 0;
  virtual void generate(generate_request_ptr req, generate_callback cb ) = 0;
  
};

}}
