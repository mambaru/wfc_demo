//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "hash_domain.hpp"
#include <unistd.h>

namespace demo{ namespace hash{

void hash_domain::initialize()
{
  /*
  for (int i =0 ; i < 100; ++i)
  {
    if ( this->global()->stop_signal_flag )
      break;
    COMMON_LOG_MESSAGE("Long initialize " << i);
    ::sleep(1);
  }
  */
}

void hash_domain::get_hash(request::get_hash::ptr req, response::get_hash::handler cb ) 
{
  if ( this->notify_ban<response::get_hash>(req, cb) )
    return;

  auto res = std::make_unique<response::get_hash>();
  res->value = std::hash< std::string >()( req->value );
  cb( std::move(res) );
}

void hash_domain::perform_io(data_ptr d, io_id_t /*io_id*/, outgoing_handler_t handler)
{
  std::string str( d->begin(), d->end() );
  size_t val = std::hash< std::string >()( str );
  std::string valstr = std::to_string(val);
  auto res = std::make_unique<data_type>( valstr.begin(), valstr.end() );
  handler( std::move(res) );
}

}}
