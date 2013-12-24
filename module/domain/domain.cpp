#include <wfc/memory.hpp>
#include <memory>
#include "domain.hpp"

#include <iostream>

namespace wamba{ namespace demo{

domain::~domain()
{
  
}

domain::domain( const domain_config& conf)
  : _conf(conf)
{
  
}

void domain::reconfigure(const domain_config& conf)
{
  _conf = conf;
}
  
void domain::initialize()
{
  if ( _demo==nullptr )
    _demo = std::make_shared<demo>();
  
  _master = std::weak_ptr<idemo>();
}
  
void domain::set( idemo::set_request_ptr req, idemo::set_callback cb )
{
  std::cout << "void domain::set( idemo::set_request_ptr req, idemo::set_callback cb )" << std::endl;
  if ( auto m = _master.lock() )
  {
    idemo::set_request_ptr cpy;
    if ( req!=nullptr )
    {
      cpy = std::make_unique<request::set>();
      cpy->name = req->name;
      if ( req->data )
      {
        cpy->data = std::make_unique<data_type>( req->data->begin(), req->data->end());
      }
    }
    m->set( std::move(cpy), nullptr );
  }
  
  if ( _demo != nullptr )
  {
    std::cout << "void domain::set( idemo::set_request_ptr req, idemo::set_callback cb ) 2" << std::endl;
    _demo->set( std::move(req), cb);
  }
}

void domain::get( idemo::get_request_ptr req, idemo::get_callback cb )
{
  if ( _demo != nullptr )
  {
    _demo->get( std::move(req), cb);
  }
}

void domain::reverse( idemo::reverse_request_ptr req, idemo::reverse_callback cb )
{
  if ( _demo != nullptr )
  {
    _demo->reverse( std::move(req), cb);
  }
}

void domain::generate( idemo::generate_request_ptr req, idemo::generate_callback cb )
{
  if ( _demo != nullptr )
  {
    _demo->generate( std::move(req), cb);
  }
}

}}
