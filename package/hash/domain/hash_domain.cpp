//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "hash_domain.hpp"
#include <hash/logger.hpp>
#include <unistd.h>
#include <wfc/logger.hpp>
#include <wfc/wfc_exit.hpp>

namespace demo{ namespace hash{

void hash_domain::initialize()
{
  //HASH_LOG_FATAL("Демо хеш кранты!")
  //wfc_exit_with_error("Демо хеш кранты!");
  /*
  std::thread([this](){
    double x = 0.1;
    while (!this->system_is_stopped() )
    {
      x+=sin(x);
    }
  }).detach();*/
}

void hash_domain::get_hash(request::get_hash::ptr req, response::get_hash::handler cb ) 
{
  if ( this->notify_ban(req, cb) )
    return;

  auto res = std::make_unique<response::get_hash>();
  res->value = std::hash< std::string >()( req->value );
  cb( std::move(res) );
}

void hash_domain::perform_io(data_ptr d, io_id_t, output_handler_t handler)
{
  HASH_LOG_MESSAGE("Демо hash_domain::perform_io!")
  COMMON_LOG_MESSAGE("Демо hash_domain::perform_io!")
  HASH_LOG_WARNING("Демо hash_domain::perform_io!")
  COMMON_LOG_WARNING("Демо hash_domain::perform_io!")
  
  //HASH_LOG_FATAL("Демо хеш кранты!")
  
  std::string str( d->begin(), d->end() );
  size_t val = std::hash< std::string >()( str );
  std::string valstr = std::to_string(val);
  auto res = std::make_unique<data_type>( valstr.begin(), valstr.end() );
  handler( std::move(res) );
}

}}
