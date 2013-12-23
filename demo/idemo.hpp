#pragma once
#include <fas/functional/tstring.hpp>
#include <wfc/callback/callback_owner.hpp>
#include <wfc/json/json.hpp>
#include <vector>
#include "api/api.hpp"

namespace wamba{ namespace demo{


struct idemo
  : wfc::callback_owner<>
{
  typedef std::unique_ptr<request::set> set_request_ptr;
  typedef std::unique_ptr<response::set> set_response_ptr;
  typedef std::function< wfc::callback_status(set_response_ptr)> set_callback;

  typedef std::unique_ptr<request::get> get_request_ptr;
  typedef std::unique_ptr<response::get> get_response_ptr;
  typedef std::function< wfc::callback_status(get_response_ptr)> get_callback;

  typedef std::unique_ptr<request::reverse> reverse_request_ptr;
  typedef std::unique_ptr<response::reverse> reverse_response_ptr;
  typedef std::function< wfc::callback_status(reverse_response_ptr)> reverse_callback;

  typedef std::unique_ptr<request::generate> generate_request_ptr;
  typedef std::unique_ptr<response::generate> generate_response_ptr;
  typedef std::function< wfc::callback_status(generate_response_ptr)> generate_callback;
  
  virtual ~idemo() {}
  
  virtual void set(set_request_ptr req, set_callback cb ) = 0;
  virtual void get(get_request_ptr req, get_callback cb ) = 0;
  virtual void reverse(reverse_request_ptr req, reverse_callback cb ) = 0;
  virtual void generate(generate_request_ptr req, generate_callback cb ) = 0;
  
};

}}
