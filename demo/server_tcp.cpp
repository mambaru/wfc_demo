
#include "server_tcp.hpp"
#include "idemo.hpp"

#include <wfc/jsonrpc/server_tcp.hpp>
#include <wfc/inet/conn/connection_context.hpp>

namespace wamba{ namespace demo{

struct _set_;

struct set_method
{
  /* {"method":"set", "id":1, "params":{"name":"aaaa", "data":[1, 2, 3, 4, 5]}};  */
  typedef request::set_json::type  invoke_request;
  typedef response::set_json::type invoke_response;
  const char* name() const { return "set";}
  
  template<typename T,  typename C>
  void request(T& t,  idemo::set_request_ptr req,  int , C callback)
  {
    if (auto demo = t.context().demo.lock() )
    {
      demo->set( std::move(req), [callback](idemo::set_response_ptr resp) {
        callback( std::move(resp), nullptr);
        return wfc::callback_status::ready;
      } );
    }
  }
};


struct _get_;

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
      demo->get( std::move(req), [callback](idemo::get_response_ptr resp) {
        callback( std::move(resp), nullptr);
        return wfc::callback_status::ready;
      } );
    }
  }
};

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
      demo->generate( std::move(req), [&t, callback](idemo::generate_response_ptr resp) {
        callback( std::move(resp), nullptr);
        //!!! 
        //std::cout << "generate_method t.shutdown()" << std::endl;
        //t.shutdown();
        return wfc::callback_status::ready;
      } );
    }
  }
};

//template<typename T>
struct demo_context//: T
{
  std::weak_ptr<idemo> demo;
};

struct aspect_methods: fas::aspect<
  wfc::jsonrpc::method<_set_,  set_method>, 
  wfc::jsonrpc::method<_get_,  get_method>, 
  wfc::jsonrpc::method<_generate_,  generate_method>
> {};

struct aspect_tcp_connection: wfc::jsonrpc::jsonrpc<
  //wfc::inet::context< wfc::jsonrpc::context_stream<demo_context> >,
  wfc::inet::context< demo_context >, 
  aspect_methods
> {};
  
class server_tcp_impl
 : public ::wfc::jsonrpc::server_tcp<aspect_tcp_connection>
{
  typedef ::wfc::jsonrpc::server_tcp<aspect_tcp_connection> super;
public:
  server_tcp_impl(std::weak_ptr< wfc::global > g, const wfc::jsonrpc::server_tcp_config& conf)
    : super(g, conf)
  {
    
  }
};

server_tcp::~server_tcp()
{
  
}

server_tcp::server_tcp(std::weak_ptr< wfc::global > g, const wfc::jsonrpc::server_tcp_config& conf)
  : _impl(std::make_unique<server_tcp_impl>(g, conf) )
{
  
}
void server_tcp::reconfigure(const wfc::jsonrpc::server_tcp_config& conf)
{
  _impl->reconfigure(conf);
}

void server_tcp::initialize(std::weak_ptr<idemo> demo)
{
  auto cntx = _impl->connection_context();
  cntx.demo = demo;
  _impl->connection_context(cntx);
  _impl->initialize();
}

void server_tcp::start()
{
  _impl->start();
}

void server_tcp::stop()
{
  _impl->stop();
}

}}
