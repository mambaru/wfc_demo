#pragma once


#include "demo_config.hpp"
#include "server_tcp.hpp"
#include <wfc/core/global.hpp>
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
  std::shared_ptr<demo> _demo;
  std::shared_ptr<server_tcp> _tcp;
  
};

}}
