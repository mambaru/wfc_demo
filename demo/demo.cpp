#include <wfc/memory.hpp>
#include "demo.hpp"

#include <unistd.h>
#include <algorithm>

namespace wamba{ namespace demo{

demo::~demo() {}

 
template<typename Req, typename Callback>
static bool check_params(Req& req, Callback& cb)
{
  if ( req==nullptr )
  {
    if (cb != nullptr )
      cb(nullptr);
    return false;
  }
  return true;
}

/*
template<typename T>
static std::unique_ptr<T> make_unique_if(bool cond)
{
  if ( !cond )
    return std::unique_ptr<T>();
  return std::unique_ptr<T>(new T());
}

template<typename T>
static std::unique_ptr<T> make_unique_if(bool cond, T value)
{
  if ( !cond )
    return std::unique_ptr<T>();
  return std::unique_ptr<T>(new T(value));
}*/

/*
template<typename Resp, typename Callback>
void call_if(Resp resp, Callback cb)
{
  if ( cb!=nullptr)
    return cb(std::move(resp));
}
*/

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique_if(bool cond, Args&& ...args )
{
  if ( cond )
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
  return std::unique_ptr<T>();
}


demo::demo(demo_ptr repli, hash_ptr hash)
  : _repli(repli)
  , _hash(hash)
{
  
}

void demo::set( idemo::set_request_ptr req, idemo::set_callback cb )
{
  if ( !check_params( req, cb) )
    return;

  auto resp = make_unique_if<response::set>(cb!=nullptr);
  auto repli = make_unique_if<request::set>(_repli!=nullptr, *req);
  
  {
    std::lock_guard<std::mutex> lk(_mutex);
    _data[ std::move(req->name) ] = std::move(req->data);
    _repli->set( std::move(repli), nullptr );
  }
  
  if ( resp!=nullptr )
  {
    resp->status = true;
    cb(std::move(resp));
  }
}

void demo::get( idemo::get_request_ptr req, idemo::get_callback cb )
{
  if (cb==nullptr)
    return;

  if ( !check_params( req, cb) )
    return;

  auto resp = std::make_unique<response::get>();
  
  auto itr = _data.find(req->name);
  std::swap(resp->name, req->name);
  
  if ( itr == _data.end() )
  {
    resp->status = false;
    cb( std::move(resp) );
  }
  else
  {
    resp->status = true;
    resp->data = itr->second;
  }
  cb( std::move(resp) );
}





}}
