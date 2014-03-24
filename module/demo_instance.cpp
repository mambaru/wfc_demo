#include "demo_instance.hpp"
#include "service/method_list.hpp"

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
}

void demo_instance::reconfigure(const demo_config& conf)
{
  _conf = conf;
  _domain->reconfigure( static_cast<const domain_config&>(conf) );
  _services->reconfigure(conf.services);
}

void demo_instance::initialize()
{
  namespace sj = wfc::service::rn::jsonrpc;
  _services->initialize( sj::make_factory<method_list>(_domain) );
  _domain->initialize();
}

void demo_instance::start()
{
  _services->start();
  _domain->start();
}

void demo_instance::stop()
{
  _services->stop();
}

demo_config demo_instance::create_config(std::string type)
{
  demo_config conf;
  conf.services = service_list::create_config(type);
  return conf;
}

}}
