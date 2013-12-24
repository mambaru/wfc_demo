

#include <wfc/jsonrpc/server_tcp_config.hpp>
#include <wfc/jsonrpc/server_tcp.hpp>
#include "connection_stream.hpp"

namespace wamba{ namespace demo{

 
class server_tcp_impl
 : public ::wfc::jsonrpc::server_tcp<connection_stream>
{
  typedef ::wfc::jsonrpc::server_tcp<connection_stream> super;
public:
  server_tcp_impl(std::weak_ptr< wfc::global > g, const wfc::jsonrpc::server_tcp_config& conf)
    : super(g, conf)
  {
  }
};

}}
