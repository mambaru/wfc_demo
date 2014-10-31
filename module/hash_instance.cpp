#include "hash_instance.hpp"
#include <hash/demo_hash.hpp>
#include "service/hash_api.hpp"

namespace wamba{ namespace demo{

hash_instance::~hash_instance()
{
}

hash_instance::hash_instance(const std::string& /*name*/, std::weak_ptr< wfc::global > g, const hash_config& conf)
{
  _services = std::make_shared< service_list >( g, conf );
  _demo_hash   = std::make_shared<demo_hash>();
}

void hash_instance::reconfigure(const hash_config& conf)
{
  _services->reconfigure(conf);
}

void hash_instance::initialize()
{
  namespace sj = wfc::service::rn::jsonrpc;
  _services->initialize( sj::make_factory< service::hash_api >(_demo_hash) );
}

void hash_instance::start()
{
  _services->start();
}

void hash_instance::stop()
{
  _services->stop();
}

void hash_instance::shutdown()
{
  _services->shutdown();
}

hash_config hash_instance::create_config(std::string type)
{
  return service_list::create_config(type);
}

}}
