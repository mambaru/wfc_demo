#include "demo_instance.hpp"
#include "service/method_list.hpp"
#include "gateway/method_list.hpp"

namespace wamba{ namespace demo{

demo_instance::~demo_instance()
{
}

demo_instance::demo_instance(const std::string& name, std::weak_ptr< wfc::global > g, const demo_config& conf)
  : _name(name)
  , _global(g)
  , _conf(conf)
  , _domain(std::make_shared<domain>(static_cast<const domain_config&>(conf)))
{
  _services = std::make_shared< service_list >( g, conf.services );
  _gateways = std::make_shared< gateway_list >( g, conf.gateways );
  _provider = std::make_shared< provider >( );
}

void demo_instance::reconfigure(const demo_config& conf)
{
  _conf = conf;
  _domain->reconfigure( static_cast<const domain_config&>(conf) );
  _services->reconfigure(conf.services);
  _gateways->reconfigure(conf.gateways);
}

void demo_instance::initialize()
{
  namespace sj = wfc::service::rn::jsonrpc;
  namespace gj = wfc::gateway::rn::jsonrpc;
  _services->initialize( sj::make_factory< service::method_list >(_domain) );
  _gateways->initialize( gj::make_factory< gateway::method_list >(_domain, _provider) );
  _domain->initialize(_provider);
}

void demo_instance::start()
{
  _gateways->start();
  _services->start();
  _domain->start();
}

void demo_instance::stop()
{
  _services->stop();
  _gateways->stop();
  //_domain->stop();
}

demo_config demo_instance::create_config(std::string type)
{
  demo_config conf;
  conf.services = service_list::create_config(type);
  conf.gateways = gateway_list::create_config(type);
  return conf;
}

}}
