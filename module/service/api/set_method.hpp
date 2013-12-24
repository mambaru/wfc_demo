#pragma once

#include <demo/idemo.hpp>
#include "../../api/set_json.hpp"

namespace wamba{ namespace demo{

struct set_method
{
  /* {"method":"set", "id":1, "params":{"name":"aaaa", "data":[1, 2, 3, 4, 5]}};  */
  typedef request::set_json::type  invoke_request;
  typedef response::set_json::type invoke_response;
  
  const char* name() const { return "set"; }
  
  template<typename T,  typename C>
  void request(T& t,  idemo::set_request_ptr req,  int , C callback)
  {
    if (auto demo = t.context().demo.lock() )
    {
      demo->set( std::move(req), [callback](idemo::set_response_ptr resp) 
      {
        callback( std::move(resp), nullptr);
        return wfc::callback_status::ready;
      });
    }
  }
};

}}
