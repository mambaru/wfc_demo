#pragma once
#include <fas/functional/tstring.hpp>
#include <wfc/callback/callback_owner.hpp>
#include <wfc/json/json.hpp>
#include <vector>
#include <demo/api/api.hpp>

namespace wamba{ namespace demo{

typedef std::vector<int> data_type;
typedef std::unique_ptr<data_type> data_ptr;

namespace request
{
  struct set {
    std::string name;
    data_ptr data;
  };  
}

namespace response
{
  struct set
  {
    bool status;
  };
}

/// get

namespace request
{
  struct get {
    std::string name;
  };
}

namespace response
{
  struct get {
    std::string name;
    data_ptr data;
  };
}

/// reverse

namespace request
{
  struct reverse 
  {
  
  };
}

namespace response
{
  struct reverse 
  {
  
  };
}

/// generate

namespace request
{
  struct generate 
  {
    size_t size;
  };
}

namespace response
{
  struct generate 
  {
    data_ptr data;
  };
}
}}
