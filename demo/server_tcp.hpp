#pragma once


#include "idemo.hpp"
#include "demo_config.hpp"
#include <wfc/core/global.hpp>
#include <wfc/jsonrpc/server_tcp_config.hpp>
#include <string>
#include <memory>

namespace wamba{ namespace demo{
  
class server_tcp_impl;
  
class server_tcp
{
public:
  virtual ~server_tcp();
  server_tcp(std::weak_ptr< wfc::global > g, const wfc::jsonrpc::server_tcp_config& conf);
  void reconfigure(const wfc::jsonrpc::server_tcp_config& conf);
  void initialize(std::weak_ptr<idemo> demo);
  void start();
  void stop();
private:
  std::unique_ptr<server_tcp_impl> _impl;
};

}}
