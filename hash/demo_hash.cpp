

#include "demo_hash.hpp"
#include <memory>
#include <functional>
#include <iostream>

namespace wamba{ namespace demo{

demo_hash::~demo_hash()
{
  
}

void demo_hash::hash(hash_request_ptr req, hash_callback cb )
{
  std::cout << "hash!" << std::endl;
  if (req==nullptr)
  {
    if (cb!=nullptr)
      cb(nullptr);
    return;
  }
  
  if (cb == nullptr)
    return;
  
  auto resp = std::unique_ptr<response::hash>(new response::hash);
  resp->result = std::hash<std::string>()(req->text);
  cb(std::move(resp));
}

}}

