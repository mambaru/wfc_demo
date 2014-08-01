#pragma once

#include "api/get.hpp"
#include "api/set.hpp"
#include "api/reverse.hpp"
#include "api/generate.hpp"

#include <memory>
#include <functional>

namespace wamba{ namespace demo{

  
struct idemo_callback
{
  typedef response::generate push_request;
  typedef bool               push_response;
  typedef std::unique_ptr<push_request> push_request_ptr;
  typedef std::unique_ptr<push_response> push_response_ptr;
  typedef std::function<void(push_response_ptr)> push_callback;
  
  virtual void push(push_request_ptr, push_callback) = 0;
};


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
  
  //typedef std::unique_ptr<response::generate> push_request_ptr;
  //typedef std::unique_ptr<bool> push_response_ptr;
  //typedef std::function<void(push_response_ptr)> push_callback;
  typedef std::function<void(idemo_callback::push_request_ptr, idemo_callback::push_callback)> generate_repli;

  
  
  virtual ~idemo() {}
  
  virtual void set(set_request_ptr req, set_callback cb ) = 0;
  virtual void get(get_request_ptr req, get_callback cb ) = 0;
  virtual void reverse(reverse_request_ptr req, reverse_callback cb ) = 0;
  virtual void generate(generate_request_ptr req, generate_callback cb, size_t io_id,  generate_repli ) = 0;
  //virtual void push(push_request_ptr, push_callback) = 0;
  
};

}}
