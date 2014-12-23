#include <wfc/memory.hpp>
#include "demo.hpp"
#include <hash/api/hash.hpp>

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

void demo::set_(request::set::ptr req, response::set::callback cb)
{
  auto resp = make_unique_if<response::set>(cb!=nullptr);
  auto repli = make_unique_if<request::set>(_repli!=nullptr, *req);
  
  {
    std::lock_guard<std::mutex> lk(_mutex);
    std::cout <<  "DEMO SET " <<  std::endl;
    _data[ std::move(req->name) ] = std::move(req->data);
    if ( _repli != nullptr )
    {
      _repli->set( std::move(repli), nullptr );
      std::cout <<  "DEMO SET REPLI" <<  std::endl;
    }
  }
  
  if ( resp!=nullptr )
  {
    resp->status = true;
    cb(std::move(resp));
  }
}

void demo::set_hash_(request::set::ptr req, response::set::callback cb)
{
  if ( auto req_hash = make_unique_if<request::hash>(
                          this->_hash != nullptr, 
                          std::move(request::hash{ std::move(req->data) })
                       ) 
     ) 
  {
    auto preq = std::make_shared<request::set::ptr>(std::move(req));
    auto pthis = this->shared_from_this();
    this->_hash->hash(std::move(req_hash), [pthis, preq, cb](std::unique_ptr<response::hash> resp) {
      if ( resp == nullptr )
      {
        pthis->set_(nullptr, cb);
      }
      else
      {
        char ch[32] = {0};
        sprintf(ch, "%lu", resp->result);
        (*preq)->data = ch;
        pthis->set_( std::move(*preq), cb);
      }
    });
  }
  else
  {
    // TODO: bad gateway
    if ( cb!=nullptr )
      cb(nullptr);
  }
}


void demo::set( request::set::ptr req, response::set::callback callback )
{
  if ( !check_params( req, callback) )
    return;
  
  if ( req->hash )
  {
    this->set_hash_(std::move(req), std::move(callback));
  }
  else
  {
    this->set_(std::move(req), std::move(callback));
  }
    
}

void demo::get( request::get::ptr req, response::get::callback cb )
{
  std::cout <<  "DEMO GET -1-" <<  std::endl;

  if (cb==nullptr)
    return;

  if ( !check_params( req, cb) )
    return;

  auto resp = std::make_unique<response::get>();
  
  auto itr = _data.find(req->name);
  std::swap(resp->name, req->name);
  
  if ( itr == _data.end() )
  {
    std::cout <<  "DEMO GET -2.1-" <<  std::endl;

    resp->status = false;
    //cb( std::move(resp) );
  }
  else
  {
    std::cout <<  "DEMO GET -2.2- [" <<  itr->second << "]" <<  std::endl;
    resp->status = true;
    resp->data = itr->second;
  }
  std::cout <<  "DEMO GET -2-" <<  std::endl;
  cb( std::move(resp) );
}





}}
