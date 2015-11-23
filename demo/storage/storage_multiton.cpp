//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "storage_multiton.hpp"
#include "storage.hpp"
#include "storage_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{ namespace storage{

WFC_NAME2(storage_object_name, "demo-storage")

class storage_multiton::impl: public ::wfc::multiton<
  storage_object_name,
  wfc::instance<storage>,
  storage_config_json
>
{  
};

storage_multiton::storage_multiton()
  : component( std::make_shared<impl>() )
{
}

}}}
