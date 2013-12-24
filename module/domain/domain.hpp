#pragma once

#include <demo/demo.hpp>
#include "domain_config.hpp"
#include <memory>

namespace wamba{ namespace demo{

class domain: public idemo
{
public:
  domain(const domain&) = delete;
  domain& operator = (const domain&) = delete;

  virtual ~domain();
  domain(const domain_config& conf);
  
  void reconfigure(const domain_config& conf);
  
  void initialize();
  
  virtual void set(set_request_ptr req, set_callback cb );
  virtual void get(get_request_ptr req, get_callback cb );
  virtual void reverse(reverse_request_ptr req, reverse_callback cb );
  virtual void generate(generate_request_ptr req, generate_callback cb );

private:
  domain_config _conf;
  std::shared_ptr<demo> _demo;
  std::weak_ptr<idemo> _master;
};

}}
