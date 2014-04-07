#pragma once

#include <demo/demo.hpp>
#include "domain_config.hpp"
#include <memory>
#include <wfc/thread/delayed_queue.hpp>
#include <thread>
#include <list>
#include <wfc/gateway/provider.hpp>
#include <wfc/io_service.hpp>

namespace wamba{ namespace demo{

typedef wfc::gateway::provider<idemo> provider_type;

class stand;
  
class domain: public idemo
{
  typedef std::shared_ptr<stand> stand_ptr;
public:
  domain(const domain&) = delete;
  domain& operator = (const domain&) = delete;

  virtual ~domain();
  domain(const domain_config& conf);
  
  void start();
  
  void reconfigure(const domain_config& conf);
  
  std::weak_ptr<provider_type> provider() const;
  //void initialize(std::weak_ptr<provider_type> provider);
  
  virtual void set(set_request_ptr req, set_callback cb );
  virtual void get(get_request_ptr req, get_callback cb );
  virtual void reverse(reverse_request_ptr req, reverse_callback cb );
  virtual void generate(generate_request_ptr req, generate_callback cb );

private:
  //wfc::io_service _io_service;
  //stand_ptr _main_stand;
  typedef std::mutex mutex_type;
  mutable std::mutex _mutex;
  domain_config _conf;
  std::shared_ptr<demo> _demo;
  std::shared_ptr<provider_type> _provider;
  std::vector<std::thread> _generate_threads;
  wfc::delayed_queue _delayed_queue;
};

}}
