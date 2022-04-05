//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "demo_multiton.hpp"
#include "demo_domain.hpp"
#include "demo_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace damba{ namespace demo{

namespace {

WFC_NAME2(object_name, "demo")

class impl: public ::wfc::multiton<
  object_name,
  wfc::instance<demo_domain>,
  demo_config_json
>
{
};

}
demo_multiton::demo_multiton()
  : component( std::make_shared<impl>() )
{
}

}}
