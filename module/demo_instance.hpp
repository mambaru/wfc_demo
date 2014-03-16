#pragma once

#include <wfc/service.hpp>

#include "demo_config.hpp"
//#include "service/server_tcp.hpp"
#include <wfc/core/global.hpp>
#include "domain/domain.hpp"
#include <string>
#include <memory>

namespace wamba{ namespace demo{
  
class demo;
  
class demo_instance
{
public:
  
  virtual ~demo_instance();
  
  demo_instance(const std::string& name, std::weak_ptr< wfc::global > g, const demo_config& conf);
  
  void reconfigure(const demo_config& conf);
  
  void initialize();
  
  void start();
  
  void stop();
  
private:
  
  std::string _name;
  std::weak_ptr< wfc::global > _global;
  demo_config _conf;
  std::shared_ptr<domain> _domain;
  typedef wfc::service::rn::jsonrpc::service_list service_list;
  std::shared_ptr< service_list > _services;
};

}}
