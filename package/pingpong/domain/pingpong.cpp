//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#include "pingpong.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <iostream>
#include <atomic>
#include <memory>
#include <chrono>
#include <iomanip>
#include <boost/concept_check.hpp>


#define PINGPONG_LOG_MESSAGE(message) WFC_LOG_MESSAGE("pingpong", message)
#define PINGPONG_LOG_DEBUG(message)   WFC_LOG_DEBUG("pingpong", message)

namespace wamba{ namespace pingpong{

namespace {

  inline void pong_result_ping(response::ping::handler cb, response::pong::ptr res)
  {
    if ( res != nullptr )
    {
      auto ping_res = std::make_unique<response::ping>();
      ping_res->ping_count = res->ping_count;
      ping_res->pong_count = res->pong_count;
      cb( std::move(ping_res) );
    }
    else
    {
      PINGPONG_LOG_MESSAGE("Pong result nullptr: Bad Gateway")
    }
  }

  template<typename T>
  void pong_send_(T req, response::ping::handler cb, ipingpong::pong_handler pong_reqester)
  {
    if ( pong_reqester != nullptr )
    {
      using namespace std::placeholders;
      auto pong_req = std::make_unique<request::pong>();
      pong_req->ping_count = req->ping_count;
      pong_req->pong_count = req->pong_count;
      pong_reqester( std::move(pong_req), std::bind( pong_result_ping, cb, _1 ) );
    }
    else
    {
      auto res = std::make_unique<response::ping>();
      res->ping_count = req->ping_count;
      res->pong_count = req->pong_count;
      cb( std::move(res));
    }
  }

}

  response::ping::handler pingpong::make_response_wrapper_(/*size_t size,*/ response::ping::handler cb, ipingpong::pong_handler pong_reqester)
  {
    typedef std::shared_ptr< std::atomic_size_t > size_ptr;
    std::tuple<size_ptr, size_ptr, size_ptr> p;
    std::get<0>(p) = std::make_shared< std::atomic_size_t >( _targets.size() );
    std::get<1>(p) =  std::make_shared< std::atomic_size_t >( 0 );
    std::get<2>(p) =  std::make_shared< std::atomic_size_t >( 0 );
    return [cb, p, pong_reqester](response::ping::ptr res)
    {
      auto& callback_counter = *std::get<0>(p);
      auto& ping_counter = *std::get<1>(p);
      auto& pong_counter = *std::get<2>(p);
      --callback_counter;
      if ( callback_counter == 0)
      {
        if ( res != nullptr )
        {
          res->ping_count += ping_counter;
          res->pong_count += pong_counter;
        }
        if ( pong_reqester!=nullptr )
        {
          ::wamba::pingpong::pong_send_( std::move(res), std::move(cb), std::move(pong_reqester) );
        }
        else if (cb != nullptr )
        {
          cb( std::move(res) );
        }
      }
      else if ( res != nullptr )
      {
        ping_counter += res->ping_count;
        pong_counter += res->pong_count;
      }
    };
  }

void pingpong::reconfigure()
{
  auto& opt = this->options();
  _deny_pong = opt.deny_pong;
  _stress_ping = opt.stress_ping;

  PINGPONG_LOG_MESSAGE("void pingpong::reconfigure()  _stress_ping= " << _stress_ping)
  _targets.clear();
  for ( auto name: opt.target_list)
  {
    if (auto p = this->global()->registry.get<ipingpong>(name))
    {
      _targets.push_back(p);
    }
  }
  
  this->global()->after_start.push_back([this]()->bool
  {
    this->stress_ping_();
    return true;
  });
}


void pingpong::reg_io(io_id_t io_id, std::weak_ptr<iinterface> witf)
{
  if ( auto p = witf.lock() )
  {
    p->perform_io( ::iow::io::make("Hello World"), 0, nullptr );
  }
}

void pingpong::startup(io_id_t, std::weak_ptr<ipingpong> witf)
{
  if ( auto p = witf.lock() )
  {
    p->pong(std::make_unique<request::pong>(), nullptr);
  }
}



/**
 * Рассылает входящий ping по целям и собирает ответы. 
 * Собрав все ответы, делает запрос pong источнику пинга
 */
void pingpong::reping_(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, pong_handler pong_reqester)
{
  using namespace std::placeholders;
  request::ping req_ping;
  req_ping.ping_count = req->ping_count;
  req_ping.pong_count = req->pong_count;

  auto callback = this->make_response_wrapper_( std::move(cb), std::move(pong_reqester) );

  for (auto t : _targets )
  {
    // TODO: сделать domain::get_io_id;
    std::shared_ptr<pingpong> pthis; // shared_from_this, wthis
    t->ping2( std::make_unique<request::ping>(req_ping), callback, -1, std::bind( &ipingpong::pong, pthis, _1, _2) );
  }
}

void pingpong::ping(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, std::weak_ptr<ipingpong> itf)
{
  using namespace std::placeholders;
  if ( auto pitf = itf.lock() )
  {
    this->ping2(std::move(req), std::move(cb), io_id, std::bind(&ipingpong::pong, pitf, _1, _2) );
  }
}

void pingpong::ping2(request::ping::ptr req, response::ping::handler cb, io_id_t io_id, pong_handler pong_reqester) 
{
  req->ping_count++;
  if ( _targets.empty() )
  {
    if ( !_deny_pong )
    {
      ::wamba::pingpong::pong_send_( std::move(req), std::move(cb), pong_reqester );
    }
    else
    {
      auto res = std::make_unique<response::ping>();
      res->ping_count = req->ping_count;
      res->pong_count = req->pong_count;
      cb( std::move(res) );
    }
    
  }
  else
  {
    this->reping_( std::move(req), std::move(cb), io_id, pong_reqester );
  }
}

void pingpong::pong(request::pong::ptr req, response::pong::handler cb ) 
{
  req->pong_count++;
  if ( cb == nullptr ) 
    return;

  auto res = std::make_unique<response::pong>();
  res->ping_count = req->ping_count;
  res->pong_count = req->pong_count;
  cb( std::move(res) );
}

void pingpong::stress_ping_( )
{
  //PINGPONG_LOG_MESSAGE("void pingpong::stress_ping_( size_t stress_ping)")
  _stat_time = std::chrono::high_resolution_clock::now();
  using namespace std::placeholders;
  size_t size = _stress_ping;
  for ( size_t i=0; i < size; ++i)
  {
    auto req = std::make_unique<request::ping>();
    req->ping_count = -1; // Локальный не считаем
    auto start = std::chrono::high_resolution_clock::now();
    this->ping2(std::move(req), this->wrap( std::bind(&pingpong::stress_result_, this, _1, start) ) , 0, nullptr );
  }
}

void pingpong::stress_result_( response::ping::ptr res, std::chrono::high_resolution_clock::time_point start )
{
  if ( res == nullptr )
  {
    PINGPONG_LOG_MESSAGE("stress_result_: BAD GATEWAY")
    return;
  }
  
  auto finish = std::chrono::high_resolution_clock::now();
  auto tm_ms = std::chrono::duration_cast< std::chrono::nanoseconds >( finish - start ).count();

  this->stat_(tm_ms, res->ping_count, res->pong_count);
  
  /*this->global()->io_service.post( this->wrap( [this]()
  {*/
    auto start1 = std::chrono::high_resolution_clock::now();
    using namespace std::placeholders;
    auto req = std::make_unique<request::ping>();
    req->ping_count = -1; // Локальный не считаем
    this->ping2(std::move(req), this->wrap( std::bind(&pingpong::stress_result_, this, _1, start1) ) , 0, nullptr );
  //}));
}

static inline long ns2rate(time_t ns, int count = 1)
{
  return ns > 0 ? 1000000000.0*count/ns : -1;
}

static inline std::string rate_fmt(std::vector<time_t>& i, size_t perc, size_t k)
{
  size_t pos = i.size()*perc / 100;
  if ( pos == i.size() )
    pos -= 1; 
    
  auto rate = ns2rate(i[pos]);
  std::stringstream ss;
  ss << perc << "% "
  << std::setprecision(3) <<  std::fixed
  << i[pos]/1000000.0 << "ms " << std::internal << rate << "("<< rate*k <<")ps\t";
  return ss.str();
}

void pingpong::stat_( time_t ms, size_t pingc, size_t pongc )
{
  static const size_t MAX_STAT = 100;
  _stat_count += 1;
  std::vector<time_t> i;
  time_t now = time(0);
  
  {
    std::lock_guard<mutex_type> lk( _mutex );
    
    if ( _show_time == now )
      return;
      
    _intervals.push_back(ms);
    if ( _intervals.size() == MAX_STAT )
    {
      _intervals.swap(i);
      _intervals.reserve(MAX_STAT);
    }
  }

  
  
  if ( !i.empty() )
  {
    auto stat_finish = std::chrono::high_resolution_clock::now();
    auto tm_ns = std::chrono::duration_cast< std::chrono::nanoseconds >( stat_finish - _stat_time ).count();
    
    size_t k = (pingc + pongc)*2; // Количество сообщений запросы+ответы
    std::sort(i.begin(), i.end());

    PINGPONG_LOG_MESSAGE(
      rate_fmt(i, 0, k) <<
      rate_fmt(i, 50, k) <<
      rate_fmt(i, 80, k) <<
      rate_fmt(i, 95, k) <<
      rate_fmt(i, 99, k) <<
      rate_fmt(i, 100, k) )
    PINGPONG_LOG_MESSAGE( 
      "Totals ping=" << pingc << " pong=" << pongc
      << std::setprecision(3) << std::fixed
      << " count=" << _stat_count << " time=" <<  tm_ns/1000000.0
      << "ms rate=" << ns2rate(tm_ns, _stat_count) << " req+res=" << k*_stat_count << "(rate: " << ns2rate(tm_ns, k*_stat_count) /*ns2rate(tm_ns, _stat_count)*k*/ << ")" 
    )
    _show_time = now;
    _stat_time = std::chrono::high_resolution_clock::now();
    _stat_count = 0;
  }
}

}}
