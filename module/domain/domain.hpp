#pragma once

#include <demo/demo.hpp>
#include "domain_config.hpp"
#include <memory>
#include <wfc/thread/delayed_queue.hpp>
#include <thread>
#include <list>
#include <wfc/provider/provider.hpp>
#include <wfc/io_service.hpp>
#include <wfc/callback/callback_owner.hpp>

namespace wamba{ namespace demo{

typedef wfc::provider::provider<idemo> provider_type;

class stand;
  
class domain
  : public idemo
{
  typedef std::shared_ptr<stand> stand_ptr;
public:
  domain(const domain&) = delete;
  domain& operator = (const domain&) = delete;

  virtual ~domain();
  domain(const domain_config& conf, std::shared_ptr<provider_type> provider);
  
  void start();
  
  void reconfigure(const domain_config& conf);
  
  virtual void set(request::set::ptr req, response::set::callback cb );
  virtual void get(request::get::ptr req, response::get::callback cb );
  
  std::shared_ptr<demo> get_demo() 
  {
    return _demo;
  }

private:
  
  domain_config _conf;
  std::shared_ptr<demo> _demo;
  std::shared_ptr<provider_type> _provider;
};

}}
