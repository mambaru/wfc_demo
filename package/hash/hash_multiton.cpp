//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "hash_multiton.hpp"
#include "hash_config_json.hpp"
#include "hash.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{ namespace hash{

WFC_NAME2(hash_object_name, "demo-hash")

class hash_multiton::impl: public ::wfc::multiton<
  hash_object_name,
  ::wfc::instance<hash>,
  hash_config_json
>
{  
};

hash_multiton::hash_multiton()
  : component( std::make_shared<impl>() )
{
}

}}}
