//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//


#include "pingpong_multiton.hpp"
#include "../pingpong/pingpong.hpp"
#include "../pingpong/pingpong_config_json.hpp"

#include <wfc/module/multiton.hpp>
#include <wfc/module/instance.hpp>
#include <wfc/name.hpp>

namespace wamba{ namespace demo{

WFC_NAME2(pingpong_object_name, "pingpong")

class pingpong_multiton_impl: public ::wfc::multiton<
  pingpong_object_name,
  wfc::instance<pingpong::pingpong>,
  pingpong::pingpong_config_json
>
{  
};

pingpong_multiton::pingpong_multiton()
  : component( std::make_shared<pingpong_multiton_impl>() )
{
}

}}
