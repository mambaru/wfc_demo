#include "demo_instance.hpp"
#include <demo/demo.hpp>

namespace wamba{ namespace demo{

demo_instance::~demo_instance()
{
}

demo_instance::demo_instance(const std::string& name, std::weak_ptr< wfc::global > g, const demo_config& conf)
  : _name(name)
  , _global(g)
  , _conf(conf)
  , _domain(std::make_shared<domain>(static_cast<const domain_config&>(conf)))
  , _tcp(std::make_shared< server_tcp>(g, conf.tcp))
{
}

void demo_instance::reconfigure(const demo_config& conf)
{
  _conf = conf;
  _domain->reconfigure( static_cast<const domain_config&>(conf) );
  _tcp->reconfigure(conf.tcp);
}

void demo_instance::initialize()
{
  _tcp->initialize(_domain);
  _domain->initialize();
}

void demo_instance::start()
{
  _tcp->start();
  _domain->start();
}

void demo_instance::stop()
{
  _tcp->stop();
}

}}
