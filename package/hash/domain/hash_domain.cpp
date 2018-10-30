//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "hash_domain.hpp"
#include <hash/logger.hpp>
#include <unistd.h>
#include <wfc/logger.hpp>
#include <wfc/logger/ilogger.hpp>
#include <wfc/wfc_exit.hpp>
#include <wlog/logger_fun.hpp>
#include <iow/logger.hpp>


namespace demo{ namespace hash{

class logger: public wfc::ilogger
{
public: 
  
  formatter_fun stdout_formatter() override
  {
    return &logger::formater;
  }
  
  static void formater(std::ostream& os, const wlog::time_point& /*tp*/,
    const std::string& /*name*/, const std::string& /*ident*/, const std::string& str)
  {
    auto beg = str.find('[');
    auto end = str.find(']');
    if ( beg!=std::string::npos && end!=std::string::npos )
      os << std::string(str.begin() + beg + 1, str.begin() + end);
    else 
      os << str;
  }
};

void hash_domain::configure() 
{
  ///! this->set_target("logger", "IOW", std::make_shared<logger>() );
  DEBUG_LOG_DEBUG("hash_domain::configure " << this->options().param)
}

void hash_domain::reconfigure() 
{
  ///! this->set_target("logger", "IOW", std::make_shared<logger>() );
  DEBUG_LOG_DEBUG("hash_domain::reconfigure " << this->options().param)
}

void hash_domain::reconfigure_basic() 
{
  DEBUG_LOG_DEBUG("hash_domain::reconfigure_basic " << this->options().param)
}

void hash_domain::initialize()
{
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
  if (d==nullptr)
    return handler(nullptr);
  
  std::string str( d->begin(), d->end() );
  size_t val = std::hash< std::string >()( str );
  std::string valstr = std::to_string(val);
  auto res = std::make_unique<data_type>( valstr.begin(), valstr.end() );
  handler( std::move(res) );
}

}}
