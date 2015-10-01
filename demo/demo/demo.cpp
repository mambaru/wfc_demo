//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>

namespace wamba{ namespace demo{
  
void demo_domain::reconfigure()
{
  std::string repli_name = this->options().repli_target;
  _reply = this->global()->registry.get<idemo>(repli_name);
  
}

void demo_domain::set(request::set::ptr req, response::set::handler cb )
{
  DOMAIN_LOG_DEBUG("void demo_domain::set(request::set::ptr req, response::set::handler cb ) cb==" << (cb!=nullptr))
  // TODO: mutex
  if (cb!=nullptr)
  {
    auto resp = std::make_unique<response::set>();
    resp->status = true;
    cb( std::move(resp));
  }
  
  auto tmp1 = this->wrap( cb );
  auto tmp2 = this->wrap(cb, [](){});
  if ( _reply != nullptr )
  {
    DOMAIN_LOG_DEBUG("set reply  {{{{ ")
    _reply->set( std::move(req), nullptr );
    DOMAIN_LOG_DEBUG("}}}}   set reply")
    
  }
}

void demo_domain::get(request::get::ptr req, response::get::handler cb ) 
{
}

void demo_domain::perform_io(data_ptr d, io_id_t /*io_id*/, outgoing_handler_t handler)
{
  std::cout << "demo_domain::perform_io" << std::endl;
  if (handler!=nullptr)
  {
    std::reverse(d->begin(), d->end()-2);
    return handler( std::move(d) );
  }
}

}}
