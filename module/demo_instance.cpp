#include "demo_instance.hpp"
#include "service/api/method_list.hpp"

namespace wamba{ namespace demo{

demo_instance::~demo_instance()
{
}

demo_instance::demo_instance(const std::string& name, std::weak_ptr< wfc::global > g, const demo_config& conf)
  : _name(name)
  , _global(g)
  , _conf(conf)
  , _domain(std::make_shared<domain>(static_cast<const domain_config&>(conf)))
  //, _tcp(std::make_shared< server_tcp>(g, conf.tcp))
{
  
  namespace sj = wfc::service::rn::jsonrpc;
  _service = std::make_shared< service_type >( g, conf.service/*, sj::make_factory<method_list>(_domain)*/ );
}

void demo_instance::reconfigure(const demo_config& conf)
{
  _conf = conf;
  _domain->reconfigure( static_cast<const domain_config&>(conf) );
  _service->reconfigure(conf.service);
}

void demo_instance::initialize()
{
  namespace sj = wfc::service::rn::jsonrpc;
  _service->initialize( sj::make_factory<method_list>(_domain) );
  _domain->initialize();
}

void demo_instance::start()
{
  _service->start();
  _domain->start();
}

void demo_instance::stop()
{
  _service->stop();
}

}}
