#pragma once

#include "idemo.hpp"
#include <hash/idemo_hash.hpp>
#include <unordered_map>
#include <mutex>

namespace wamba{ namespace demo{

class demo
  : public idemo
{
public:
  typedef std::shared_ptr<idemo>      demo_ptr;
  typedef std::shared_ptr<idemo_hash> hash_ptr;
  demo(const demo&) = delete;
  demo& operator = (const demo&) = delete;

  virtual ~demo();
  demo(demo_ptr repli, hash_ptr hash);
  
  virtual void set(set_request_ptr req, set_callback cb );
  virtual void get(get_request_ptr req, get_callback cb );
  
private:
  std::mutex _mutex;
  std::unordered_map< std::string, data_type> _data;
  demo_ptr _repli;
  hash_ptr _hash;
};

}}
