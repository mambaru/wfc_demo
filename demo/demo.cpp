#include <wfc/memory.hpp>
#include "demo.hpp"

#include <unistd.h>

namespace wamba{ namespace demo{

demo::~demo()
{
  
}

demo::demo()
{
  
}
  
void demo::set( idemo::set_request_ptr req, idemo::set_callback cb )
{
  _data[ std::move(req->name) ] = std::move(req->data);
  if (cb != nullptr )
    cb( std::make_unique<response::set>(response::set{true}));
    
}

void demo::get( idemo::get_request_ptr req, idemo::get_callback cb )
{
  if (cb==nullptr)
    return;
    
  auto itr = _data.find(req->name);
  if (itr == _data.end() )
  {
    cb( std::make_unique<response::get>(response::get{req->name, nullptr}));
    return;
  }
    
  if (itr->second->size() < 1024 )
  {
    get_response_ptr res = std::make_unique<response::get>();
    res->name = std::move(req->name);
    res->data = std::make_unique<data_type>(itr->second->begin(),  itr->second->end());
    cb( std::move(res) );
  }
  else
    abort(); // TODO: в очередь

}

void demo::reverse( idemo::reverse_request_ptr /*req*/, idemo::reverse_callback /*cb*/ )
{
  
}

void demo::generate( idemo::generate_request_ptr req, idemo::generate_callback cb )
{
  if (cb==nullptr)
    return;

  //sleep(10);
  /*cb(nullptr);
  return;*/
  auto resp = std::make_unique<response::generate>();
  resp->data= std::make_unique<data_type>();
  if (req != nullptr )
  {
    resp->data->resize( req->size );
    for ( size_t i=0 ; i < req->size; ++i)
      (*resp->data)[i]=i;
  }
  
  cb( std::move(resp) );
  
}


}}
