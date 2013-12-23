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
  , _demo(std::make_shared< demo>())
  , _tcp(std::make_shared< server_tcp>(g, conf.tcp))
{
}

void demo_instance::reconfigure(const demo_config& conf)
{
  _conf = conf;
  _tcp->reconfigure(conf.tcp);
}

void demo_instance::initialize()
{
  _tcp->initialize(_demo);
}

void demo_instance::start()
{
  _tcp->start();
}

void demo_instance::stop()
{
  _tcp->stop();
}

}}
