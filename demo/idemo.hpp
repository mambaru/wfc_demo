#pragma once
#include <fas/functional/tstring.hpp>
#include <wfc/callback/callback_owner.hpp>
#include <wfc/json/json.hpp>
#include <vector>

namespace wamba{ namespace demo{

typedef std::vector<int> data_type;
typedef std::unique_ptr<data_type> data_ptr;

typedef wfc::json::array< 
  std::vector< wfc::json::value<int> >,
  fas::int_<10>
> data_type_json;

typedef wfc::json::pointer<data_ptr, data_type_json> data_ptr_json;

/// set

namespace request{
  struct set {
    std::string name;
    data_ptr data;
  };
  
  struct set_json
  {
    FAS_NAME(name)
    FAS_NAME(data)
    
    typedef wfc::json::object<
      set,
      fas::type_list_n<
        wfc::json::member<n_name, set, std::string, &set::name>,
        wfc::json::member<n_data, set, data_ptr,    &set::data, data_ptr_json >
      >::type
    > type;
  };
}

namespace response{
  
  struct set {
    bool status;
  };
  
  struct set_json
  {
    FAS_NAME(status)
   
    typedef wfc::json::object<
      set,
      fas::type_list_n<
        wfc::json::member<n_status, set, bool, &set::status>
      >::type
    > type;
  };
}

/// get

namespace request{
  struct get {
    std::string name;
  };

  struct get_json
  {
    FAS_NAME(name)
   
    typedef wfc::json::object<
      get,
      fas::type_list_n<
        wfc::json::member<n_name, get, std::string, &get::name>
      >::type
    > type;
  };
}

namespace response{
  struct get {
    std::string name;
    data_ptr data;
  };
  
  struct get_json
  {
    FAS_NAME(name)
    FAS_NAME(data)
    
    typedef wfc::json::object<
      get,
      fas::type_list_n<
        wfc::json::member<n_name, get, std::string, &get::name>,
        wfc::json::member<n_data, get, data_ptr,    &get::data, data_ptr_json >
      >::type
    > type;
  };
}

/// reverse

namespace request{
  struct reverse {
  
  };
}

namespace response{
  struct reverse {
  
  };
}

/// generate

namespace request{
  struct generate {
    size_t size;
  };
  
  struct generate_json
  {
    FAS_NAME(size)
    
    typedef wfc::json::object<
      generate,
      fas::type_list_n<
        wfc::json::member<n_size, generate, size_t, &generate::size>
      >::type
    > type;
  };
}

namespace response{
  struct generate {
    data_ptr data;
  };
  
  struct generate_json
  {
    FAS_NAME(data)
    
    typedef wfc::json::object<
      generate,
      fas::type_list_n<
        wfc::json::member<n_data, generate, data_ptr,    &generate::data, data_ptr_json >
      >::type
    > type;
  };

}

struct idemo
  : wfc::callback_owner<>
{
  typedef std::unique_ptr<request::set> set_request_ptr;
  typedef std::unique_ptr<response::set> set_response_ptr;
  typedef std::function< wfc::callback_status(set_response_ptr)> set_callback;

  typedef std::unique_ptr<request::get> get_request_ptr;
  typedef std::unique_ptr<response::get> get_response_ptr;
  typedef std::function< wfc::callback_status(get_response_ptr)> get_callback;

  typedef std::unique_ptr<request::reverse> reverse_request_ptr;
  typedef std::unique_ptr<response::reverse> reverse_response_ptr;
  typedef std::function< wfc::callback_status(reverse_response_ptr)> reverse_callback;

  typedef std::unique_ptr<request::generate> generate_request_ptr;
  typedef std::unique_ptr<response::generate> generate_response_ptr;
  typedef std::function< wfc::callback_status(generate_response_ptr)> generate_callback;
  
  virtual ~idemo() {}
  
  virtual void set(set_request_ptr req, set_callback cb ) = 0;
  virtual void get(get_request_ptr req, get_callback cb ) = 0;
  virtual void reverse(reverse_request_ptr req, reverse_callback cb ) = 0;
  virtual void generate(generate_request_ptr req, generate_callback cb ) = 0;
  
};

}}
