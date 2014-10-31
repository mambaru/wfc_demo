#pragma once

#include <wfc/service.hpp>
#include <wfc/gateway.hpp>
#include <wfc/core/global.hpp>
#include "domain/domain.hpp"
#include <string>
#include <memory>

namespace wamba{ namespace demo{
  
class demo_hash;

typedef wfc::service::rn::jsonrpc::service_list_config hash_config;


class hash_instance
{
public:

  virtual ~hash_instance();
  
  hash_instance(const std::string& name, std::weak_ptr< wfc::global > g, const hash_config& conf);
  
  void reconfigure(const hash_config& conf);
  
  void initialize();
  
  void start();
  
  void stop();
  
  void shutdown();
  
  static hash_config create_config(std::string type);
  
private:
  typedef wfc::service::rn::jsonrpc::service_list service_list;
  std::shared_ptr< service_list > _services;
  std::shared_ptr< demo_hash > _demo_hash;
};

}}
