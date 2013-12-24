#include "server_tcp.hpp"
#include "server_tcp_impl.hpp"

#include <demo/idemo.hpp>
#include <wfc/jsonrpc/server_tcp_config.hpp>
#include <wfc/core/global.hpp>

#include <memory>

namespace wamba{ namespace demo{

server_tcp::~server_tcp()
{
  
}

server_tcp::server_tcp(std::weak_ptr< wfc::global > g, const wfc::jsonrpc::server_tcp_config& conf)
  : _impl(std::make_unique<server_tcp_impl>(g, conf) )
{
  
}

void server_tcp::reconfigure(const wfc::jsonrpc::server_tcp_config& conf)
{
  _impl->reconfigure(conf);
}

void server_tcp::initialize(std::weak_ptr<idemo> demo)
{
  auto cntx = _impl->connection_context();
  cntx.demo = demo;
  _impl->connection_context(cntx);
  _impl->initialize();
}

void server_tcp::start()
{
  _impl->start();
}

void server_tcp::stop()
{
  _impl->stop();
}

}}
