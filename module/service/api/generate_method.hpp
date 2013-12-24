#pragma once

#include <demo/idemo.hpp>
#include "../../api/generate_json.hpp"
#include <wfc/logger.hpp>

namespace wamba{ namespace demo{

struct _generate_;

struct generate_method
{
  /* {"method":"generate", "id":1, "params":{"size":10000000}};  */
  /* {"method":"generate", "id":1, "params":{"size":1000}};  */
  
  typedef request::generate_json::type  invoke_request;
  typedef response::generate_json::type invoke_response;
  
  const char* name() const { return "generate";}
  
  template<typename T, typename C>
  void request(T& t,  idemo::generate_request_ptr req,  int, C callback)
  {
    if (auto demo = t.context().demo.lock() )
    {
      demo->generate( std::move(req), [&t, callback](idemo::generate_response_ptr resp)  
      {
        wfc::callback_status s = callback( std::move(resp), nullptr);
        if ( s == wfc::callback_status::died )
        {
          COMMON_LOG_MESSAGE("generate Умерло")
        }
        else
        {
          COMMON_LOG_MESSAGE("generate sended " << int(s) )
        }
        
      });
    }
  }
};


}}
