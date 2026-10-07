//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2015-2018, 2022, 2026
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <wfc/domain_object.hpp>
#include <hash/domain/hash_config.hpp>
#include <hash/ihash.hpp>

namespace damba{ namespace hash{

class hash_domain
  : public ::wfc::domain_object<ihash, hash_config>
{
public:
  virtual void reg_io(io_id_t io_id, std::weak_ptr<iinterface> itf) override;
  virtual void unreg_io(io_id_t io_id) override;
  virtual void perform_io(data_ptr d, io_id_t, output_handler_t handler) override;
  virtual void get_hash( request::get_hash::ptr req, response::get_hash::handler cb ) override;
};

}}
