#pragma once

#include "idemo.hpp"
#include <unordered_map>

namespace wamba{ namespace demo{

class demo: public idemo
{
public:
  demo(const demo&) = delete;
  demo& operator = (const demo&) = delete;

  virtual ~demo();
  demo();
  
  virtual void set(set_request_ptr req, set_callback cb );
  virtual void get(get_request_ptr req, get_callback cb );
  virtual void reverse(reverse_request_ptr req, reverse_callback cb );
  virtual void generate(generate_request_ptr req, generate_callback cb );

private:
  
  std::unordered_map< std::string, data_ptr> _data;
};

}}
