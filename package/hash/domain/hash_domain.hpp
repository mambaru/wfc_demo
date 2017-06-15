//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include <hash/domain/hash_config.hpp>
#include <hash/ihash.hpp>

namespace demo{ namespace hash{

class hash_domain
  : public ::wfc::domain_object<ihash, hash_config>
{
public:
  virtual void perform_io(data_ptr d, io_id_t /*io_id*/, outgoing_handler_t handler) override;
  virtual void get_hash( request::get_hash::ptr req, response::get_hash::handler cb ) override;
};

}}
