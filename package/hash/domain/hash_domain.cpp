//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017-2018, 2022, 2024, 2026
//
// Copyright: See COPYING file that comes with this distribution
//

#include "hash_domain.hpp"
#include <wfc/logger.hpp>
#include <chrono>

namespace damba{ namespace hash{

void hash_domain::reg_io(io_id_t io_id, std::weak_ptr<iinterface> )
{
  wfc::only_for_log(io_id);
  DEBUG_LOG_DEBUG("hash_domain::reg_io " << io_id)
}

void hash_domain::unreg_io(io_id_t io_id)
{
  wfc::only_for_log(io_id);
  DEBUG_LOG_DEBUG("hash_domain::unreg_io " << io_id)
}

void hash_domain::get_hash(request::get_hash::ptr req, response::get_hash::handler cb )
{
  if ( this->notify_ban(req, cb) )
    return;

  size_t value = std::hash<std::string>()( req->value );
  auto send = [cb, value]()
  {
    auto res = std::make_unique<response::get_hash>();
    res->value = value;
    cb( std::move(res) );
  };

  int delay = this->options().delay_ms;
  if ( delay > 0 )
  {
    this->get_workflow()->post(
      std::chrono::milliseconds(delay),
      this->callback( std::move(send) )
    );
    return;
  }

  send();
}

void hash_domain::perform_io(data_ptr d, io_id_t id, output_handler_t handler)
{
  if ( this->perform_status(d, handler ) )
    return;

  std::string str( d->begin(), d->end() );
  size_t val = std::hash< std::string >()( str );
  auto send = [handler, val]()
  {
    handler( iow::io::make(std::to_string(val)) );
  };

  int delay = this->options().delay_ms;
  if ( delay > 0 )
  {
    this->get_workflow()->post(
      std::chrono::milliseconds(delay),
      this->tracking( id, std::move(send), [](){ DOMAIN_LOG_MESSAGE("hash perform_io canceled") } )
    );
    return;
  }

  send();
}

}}
