#pragma once

#include <demo/idemo.hpp>
#include "../../api/get_json.hpp"

namespace wamba{ namespace demo{

struct get_method
{
  /* {"method":"get", "id":1, "params":{"name":"aaaa"}};  */
  /* {"method":"get", "id":1, "params":{"name":"bbbb"}};  */
  
  typedef request::get_json::type  invoke_request;
  typedef response::get_json::type invoke_response;
  
  const char* name() const { return "get";}
  
  template<typename T,  typename C>
  void request(T& t,  idemo::get_request_ptr req,  int , C callback)
  {
    if (auto demo = t.context().demo.lock() )
    {
      demo->get( std::move(req), [callback](idemo::get_response_ptr resp) 
      {
        callback( std::move(resp), nullptr);
        return wfc::callback_status::ready;
      });
    }
  }
};

}}
