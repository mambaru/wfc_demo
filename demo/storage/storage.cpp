//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "storage.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>

namespace wamba{ namespace demo{ namespace storage{
  
void storage::reconfigure()
{
  std::string repli_name = this->options().repli_target;
  _reply = this->global()->registry.get<istorage>(repli_name);
}

void storage::set(request::set::ptr req, response::set::handler cb )
{
  DOMAIN_LOG_DEBUG("void storage::set(request::set::ptr req, response::set::handler cb ) cb==" << (cb!=nullptr))
  // TODO: mutex
  if (cb!=nullptr)
  {
    auto resp = std::make_unique<response::set>();
    resp->status = true;
    cb( std::move(resp));
    cb=nullptr;
  }

  if ( _reply != nullptr )
  {
    _reply->set( std::move(req), nullptr );
  }
}

void storage::get(request::get::ptr req, response::get::handler cb ) 
{
}

void storage::perform_io(data_ptr d, io_id_t /*io_id*/, outgoing_handler_t handler)
{
  std::cout << "storage::perform_io" << std::endl;
  if (handler!=nullptr)
  {
    std::reverse(d->begin(), d->end()-2);
    return handler( std::move(d) );
  }
}

}}}
