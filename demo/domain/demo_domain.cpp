//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_domain.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>



#include "../gateway/method_list.hpp"

namespace wamba{ namespace demo{

void demo_domain::set(request::set::ptr /*req*/, response::set::callback cb )
{
  if (cb!=nullptr)
  {
    auto resp = std::make_unique<response::set>();
    resp->status = true;
    cb( std::move(resp));
  }

}

void demo_domain::get(request::get::ptr req, response::get::callback cb ) 
{
  demo_method_list1 ml;
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
