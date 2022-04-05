#pragma once

#include <pingpong/iponger.hpp>
#include <pingpong/ipinger.hpp>
#include <pingpong/api/ball_json.hpp>
#include <wfc/jsonrpc.hpp>


namespace damba{ namespace pingpong{ namespace gateway{

JSONRPC_TAG(pong)
JSONRPC_TAG(play)

template<typename Base>
class pinger_interface: public Base
{
public:
  typedef Base super;
  typedef typename super::io_id_t io_id_t;

  virtual void play(ball::ptr req, ball::handler cb ) override
  {
    this->template call<_play_>( std::move(req), cb, nullptr);
  }
  
  virtual void pong(ball::ptr req, ball::handler cb, io_id_t, ipinger::ball_handler ) override
  {
    this->template call<_pong_>( std::move(req), cb, nullptr);
  }
   
};

struct pinger_method_list: wfc::jsonrpc::method_list
<
  wfc::jsonrpc::interface_<ipinger>,
  wfc::jsonrpc::call_method< _play_, ball_json, ball_json>,
  wfc::jsonrpc::call_method< _pong_, ball_json, ball_json>
>
{
};

}}}
