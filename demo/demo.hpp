#pragma once

#include "idemo.hpp"
#include <hash/idemo_hash.hpp>
#include <unordered_map>
#include <mutex>

namespace wamba{ namespace demo{

class demo
  : public idemo
  , public std::enable_shared_from_this<demo>
{
public:
  typedef std::shared_ptr<idemo>      demo_ptr;
  typedef std::shared_ptr<idemo_hash> hash_ptr;
  demo(const demo&) = delete;
  demo& operator = (const demo&) = delete;

  virtual ~demo();
  demo(demo_ptr repli, hash_ptr hash);
  
  virtual void set(request::set::ptr req, response::set::callback cb );
  virtual void get(request::get::ptr req, response::get::callback cb );

protected:
  void set_(request::set::ptr req, response::set::callback cb);
  void set_hash_(request::set::ptr req, response::set::callback cb);
private:
  std::mutex _mutex;
  std::unordered_map< std::string, data_type> _data;
  demo_ptr _repli;
  hash_ptr _hash;
};

}}
