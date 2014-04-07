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

domain::domain( const domain_config& conf)
  : /*_main_stand( std::make_shared<strand_type>(_io_service) )
  ,*/ _conf(conf)
  , _provider( std::make_shared<provider_type>() )
{
  
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
}

std::weak_ptr<provider_type> domain::provider() const 
{
  return _provider;
}
/*
void domain::initialize(std::weak_ptr<provider_type> provider)
{
  
  
  // _provider = provider;
}*/

  
void domain::set( idemo::set_request_ptr req, idemo::set_callback cb )
{
  std::lock_guard<mutex_type> lk(_mutex);
  
  /*if ( auto p = _provider.lock() )
  {*/
    if ( auto cli = _provider->get().lock() )
    {
      std::cout << "gateway::set ready" << std::endl;
      cli->set( std::make_unique<request::set>(*req), nullptr );
    }
    // TODO: сделать через конструктор копии
    /*
    idemo::set_request_ptr cpy;
    if ( req!=nullptr )
    {
      cpy = std::make_unique<request::set>();
      cpy->name = req->name;
      if ( req->data )
      {
        cpy->data = std::make_unique<data_type>( req->data->begin(), req->data->end());
      }
      m->set( std::move(cpy), nullptr );
    }
    */
  /*}
  else
  {
    std::cout << "gateway::set not ready" << std::endl;
  }*/
  
  if ( _demo != nullptr )
  {
    _demo->set( std::move(req), cb);
  }
}

void domain::get( idemo::get_request_ptr req, idemo::get_callback cb )
{
  std::lock_guard<mutex_type> lk(_mutex);
  
  if ( _demo != nullptr )
  {
    _demo->get( std::move(req), cb);
  }
}

void domain::reverse( idemo::reverse_request_ptr req, idemo::reverse_callback cb )
{
  std::lock_guard<mutex_type> lk(_mutex);
  
  if ( _demo != nullptr )
  {
    _demo->reverse( std::move(req), cb);
  }
}

void domain::generate( idemo::generate_request_ptr req, idemo::generate_callback cb )
{
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
}

}}
