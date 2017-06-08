//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "hash.hpp"
#include "api/types.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>
#include <functional>


namespace wamba{ namespace demo{ namespace hash{

void hash::get_hash(request::get_hash::ptr req, response::get_hash::handler cb ) 
{
  if ( this->notify_ban<response::get_hash>(req, cb) )
    return;

  auto res = std::make_unique<response::get_hash>();
  res->status=true;

  typedef ::wamba::demo::hash::data_type data_type;
  res->value = std::hash< data_type >()( req->value );
  cb( std::move(res) );
}

}}}
