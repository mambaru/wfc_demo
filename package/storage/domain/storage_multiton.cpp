//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "storage_multiton.hpp"
#include "storage_domain.hpp"
#include "storage_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace demo{ namespace storage{

namespace {
  
WFC_NAME2(object_name, "demo-storage")

class impl: public ::wfc::multiton<
  object_name,
  wfc::instance<storage_domain>,
  storage_config_json
>
{  
};

}
storage_multiton::storage_multiton()
  : component( std::make_shared<impl>() )
{
}

}}
