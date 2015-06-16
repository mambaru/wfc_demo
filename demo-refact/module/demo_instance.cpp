#include <demo/demo.hpp>
#include "demo_instance.hpp"
#include "service/method_list.hpp"
#include "gateway/method_list.hpp"


namespace wamba{ namespace demo{

demo_instance::~demo_instance()
{
}

demo_instance::demo_instance(const std::string& name, std::shared_ptr< wfc::global > g, const demo_config& conf)
  : _name(name)
  , _global(g)
  , _conf(conf)
{
  _global->idle.push_back([](){std::cout << "Demo idle" << std::endl;});
  
  _services = std::make_shared< service_list >( g, conf.services );
  _gateways = std::make_shared< gateway_list >( g, conf.gateways );
  _provider = std::make_shared< provider >( g->io_service, conf.provider );
  _hash_provider = std::make_shared< hash_provider >( g->io_service, conf.provider );
  _hash_proxy = std::make_shared< gateway::hash_proxy>(_hash_provider);
  _demo   = std::make_shared<demo>(nullptr, nullptr);
}

void demo_instance::reconfigure(const demo_config& conf)
{
  _conf = conf;
  //_domain->reconfigure( static_cast<const domain_config&>(conf) );
  _provider->reconfigure(conf.provider);
  _services->reconfigure(conf.services);
  _gateways->reconfigure(conf.gateways);
}

void demo_instance::initialize()
{
  namespace sj = wfc::service::rn::jsonrpc;
  namespace gj = wfc::gateway::rn::jsonrpc;
  _services->initialize( sj::make_factory< service::demo_api >(_demo) );
  _gateways->initialize( gj::make_factory< gateway::demo_api >(_demo, _provider ) );
  //_domain->initialize(_provider);
}

void demo_instance::start()
{
  DEBUG_LOG_MESSAGE("void demo_instance::start()")
  _gateways->start();
  DEBUG_LOG_BEGIN("_services->start()")
  _services->start();
  DEBUG_LOG_END("_services->start()")
  //_domain->start();
}

void demo_instance::stop()
{
  _services->stop();
  _gateways->stop();
  
  _services.reset();
  _gateways.reset();
  //_domain.reset();
}

void demo_instance::shutdown()
{
  _services->shutdown();
  _gateways->shutdown();
  
  _services.reset();
  _gateways.reset();
  //_domain.reset();
}

demo_config demo_instance::create_config(std::string type)
{
  demo_config conf;
  conf.services = service_list::create_config(type);
  conf.gateways = gateway_list::create_config(type);
  return conf;
}

}}
