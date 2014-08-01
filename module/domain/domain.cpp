#include <wfc/memory.hpp>
#include <wfc/io/io_base.hpp>
//#include <wfc/jsonrpc/errors/error.hpp>
#include <memory>
#include "domain.hpp"

#include <iostream>

namespace wamba{ namespace demo{

  /*
class stand: public wfc::io::basic_io<>
{
  typedef wfc::io::basic_io<> super;
  
public:
  
  stand(): super(_io_service)
  {
    super::create(*this);
  }
  
  void start()
  {
    _thread = std::thread([this]()
    {
      wfc::io_service::work wrk(_io_service);
      _io_service.run();
    });
  }
  
  void stop()
  {
    _io_service.stop();
    _thread.join();
  }
  
private:
  wfc::io_service _io_service;
  std::thread _thread;
};
  */
domain::~domain()
{
  
}

domain::domain( const domain_config& conf, std::shared_ptr<provider_type> provider)
  : _provider( provider )
{
  this->reconfigure(conf);
}

void domain::reconfigure(const domain_config& conf)
{
  std::lock_guard<mutex_type> lk(_mutex);
  
  _conf = conf;
  
  if ( _conf.is_proxy)
  {
    _demo.reset();
  }
  else if (_demo==nullptr)
  {
    _demo = std::make_shared<demo>();
  }
}

void domain::start()
{
  /*
  if ( _conf.generate_threads < _generate_threads.size() )
  {
    _generate_threads.resize(_conf.generate_threads);
  }
  else
  {
    while ( _conf.generate_threads != _generate_threads.size() )
    {
      _generate_threads.push_back(std::thread([this]() 
      {
        this->_delayed_queue.run();
      }));
    }
  }
  */
}

/*
std::weak_ptr<provider_type> domain::provider() const 
{
  return _provider;
}
*/
/*
void domain::initialize(std::weak_ptr<provider_type> provider)
{
  
  
  // _provider = provider;
}*/

  
void domain::set( idemo::set_request_ptr req, idemo::set_callback cb )
{
  std::lock_guard<mutex_type> lk(_mutex);
  auto cli = _provider->get();
  if ( _demo==nullptr && cli==nullptr )
  {
    return cb(nullptr);
  }
  
  idemo::set_request_ptr req_cpy = nullptr;
  if ( cli!=nullptr && _demo!= nullptr )
  {
    req_cpy = std::make_unique<request::set>(*req);
  }

 
  if ( _demo!=nullptr )
  {
    _demo->set( std::move(req), cb);
    if ( cli!=nullptr )
      req = std::move(req_cpy);
  }
  
  //std::cout << "data size " << req->data.size() << std::endl;
  
  if ( cli!=nullptr )
  {
    if ( _demo!=nullptr )
    {
      _provider->post( &idemo::set, std::move(req), idemo::set_callback(nullptr) );
    }
    else
    {
      cli->set( std::move(req), cb);
    }
  }

}

void domain::get( idemo::get_request_ptr req, idemo::get_callback cb )
{
  std::lock_guard<mutex_type> lk(_mutex);
  
  if ( _demo != nullptr )
  {
    _demo->get( std::move(req), cb);
  }
  else if (auto cli = _provider->get() )
  {
    cli->get( std::move(req), cb);
  }
}

void domain::reverse( idemo::reverse_request_ptr req, idemo::reverse_callback cb )
{
  std::lock_guard<mutex_type> lk(_mutex);
  
  if ( _demo != nullptr )
  {
    _demo->reverse( std::move(req), cb);
  }
  else if (auto cli = _provider->get() )
  {
    cli->reverse( std::move(req), cb);
  }
}

void domain::generate( idemo::generate_request_ptr req, idemo::generate_callback cb, size_t io_id,  generate_repli repli)
{
  std::lock_guard<mutex_type> lk(_mutex);
  
  if ( _demo != nullptr )
  {
    _demo->generate( std::move(req), cb, io_id, repli);
  }
  else if (auto cli = _provider->get() )
  {
    cli->generate( std::move(req), cb, io_id, repli);
  }

  /*
  std::lock_guard<mutex_type> lk(_mutex);
  
  if ( _demo == nullptr )
    cb(nullptr);

  if (req == nullptr )
    cb(nullptr);

  if (_conf.generate_threads == 0)
  {
    _demo->generate( std::move(req), cb);
  }
  else
  {
    //auto wrp = wfc::unique_wrap( std::move(req) );
    auto wrp = std::make_shared<idemo::generate_request_ptr>( std::move(req) );
    _delayed_queue.delayed_post(std::chrono::seconds(10), [this, wrp,  cb]() 
    {
      //_demo->generate( wfc::unique_unwrap(wrp), cb);
      _demo->generate( std::move(*wrp), cb);
    });
  }
  */
}

}}
