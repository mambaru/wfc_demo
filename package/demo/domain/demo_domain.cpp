//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2017-2018, 2020-2022, 2026
//
// Copyright: See COPYING file that comes with this distribution
//

#include "demo_domain.hpp"
#include <wfc/logger.hpp>
#include <wfc/memory.hpp>
#include <wrtstat/wrtstat.hpp>
#include <iostream>
#include <functional>

namespace damba{ namespace demo{

// Домен — реализация idemo. JSON-RPC метод приходит сюда как request + callback.
// Ответ всегда через cb: объект с полями или cb(nullptr) = «сервис недоступен».
//
// Данные лежат в локальном demostg (_demo). Хеш считает соседний домен ihash
// (_hash). Связка типичная для WFC: get_target<интерфейс>(имя из конфига).

void demo_domain::initialize()
{
  // Уже после configure(): свой JSON разобран, соседи есть в реестре.
  std::string hash_name = this->options().hash_target;
  // Ищем экземпляр ihash по имени, например "hash1". Если не найден —
  // get_target по умолчанию аварийно завершит процесс (см. disabort).
  _hash = this->get_target<ihash>(hash_name);
}

// set: и обычный запрос (есть id, ждём ответ), и notify (без id, cb == nullptr).

void demo_domain::set(request::set::ptr req, response::set::handler cb )
{
  // suspend / останов / req == nullptr — cb уже вызван внутри, нам делать нечего.
  if ( this->bad_request(req, cb) )
    return;

  // Notify: cb == nullptr → res == nullptr. Запрос: новый response::set.
  auto res = this->create_response(cb);

  // emplace: true только если ключа ещё не было. Повторный set того же ключа — false.
  bool status = _demo.set(req->key, req->value);

  // В notify res пустой — статус клиенту не отправляем, но в хранилище запись уже есть.
  if ( res!=nullptr )
    res->status = status;

  // Если cb пустой, просто ничего не пошлёт. Иначе cb(res).
  this->send_response( std::move(res), std::move(cb) );
}

// get: только запрос. Notify здесь бессмысленен (нечего подтверждать).

void demo_domain::get(request::get::ptr req, response::get::handler cb )
{
  // Как bad_request, плюс отказ, если cb == nullptr (notify).
  if ( this->notify_ban(req, cb) )
    return;

  // После notify_ban cb не пустой → res всегда валидный объект.
  auto res = this->create_response(cb);

  // false / пустая value, если ключа нет. Клиент отличает это по status.
  res->status = _demo.get(req->key, &res->value);

  // Можно звать cb напрямую: notify мы уже отсекли.
  cb( std::move(res) );
}

// multiget: пачка ключей, всё синхронно, один ответ.

void demo_domain::multiget(request::multiget::ptr req, response::multiget::handler cb )
{
  if ( this->notify_ban(req, cb) )
    return;

  auto res = std::make_unique<response::multiget>();
  // Буфер на одну строку. После move в карту pval становится пустым.
  std::shared_ptr<std::string> pval;
  for (const std::string& key : req->keys )
  {
    // Новый буфер только если предыдущий уже отдали в values.
    if ( pval == nullptr )
      pval = std::make_shared<std::string>();

    if ( _demo.get(key, &*pval) )
      res->values[key] = std::move(pval);  // ключ найден — забираем указатель
    else
      res->values[key] = nullptr;          // ключа нет — в JSON будет null
  }
  cb( std::move(res) );
}

// get_hashed: своё хранилище + чужой hash.
// 1) читаем value у себя  2) отдаём в ihash::get_hash  3) в callback собираем ответ.

void demo_domain::get_hashed( request::get_hashed::ptr req, response::get_hashed::handler cb )
{
  if ( this->notify_ban(req, cb) )
    return;

  // Таргет не сконфигурирован или не поднялся — для клиента это «нет сервиса».
  if ( _hash == nullptr )
    return cb(nullptr);

  std::string value;
  if ( _demo.get( req->key, &value) )
  {
    typedef hash::request::get_hash  hash_request;
    typedef hash::response::get_hash hash_response;
    auto req_hash = std::make_unique< hash_request >();
    req_hash->value = value;  // хешируем содержимое, не ключ

    // this->callback: если нас уже stop(), лямбда не стрельнет в разрушенный this.
    // Сам hash может ответить позже и с другого потока.
    _hash->get_hash( std::move(req_hash), this->callback([cb]( hash_response::ptr res_hash)
    {
      // Сосед недоступен / оборвал вызов — так же обрываем клиента.
      if ( res_hash == nullptr )
      {
        cb( nullptr );
        return;
      }

      auto res = std::make_unique<response::get_hashed>();
      res->status = true;
      res->value = res_hash->value;
      cb( std::move(res) );
    }));
  }
  else
  {
    // Ключа нет: это не ошибка сервиса, а обычный «не найдено».
    auto res = std::make_unique<response::get_hashed>();
    res->status = false;
    cb( std::move(res) );
  }
}

// multiget_hashed: N вызовов get_hash → один ответ клиенту (fan-in).
//
// Отсутствующие ключи сразу пишем как null. Остальные уходят в hash.
// Ответы могут прийти с разных потоков — сборка под mutex.
//
// presp / psize / pmutex в shared_ptr, чтобы лямбды пережили этот стек.
// map в ответе: порядок ключей не обещаем (см. вариант 2).

void demo_domain::multiget_hashed( request::multiget_hashed::ptr req, response::multiget_hashed::handler cb)
{
  if ( this->notify_ban(req, cb) )
    return;

  if ( _hash==nullptr )
    return cb(nullptr);

  // shared_ptr на unique_ptr ответа: лямбды держат presp, а не сам объект.
  auto presp = std::make_shared<response::multiget_hashed::ptr>();
  *presp = std::make_unique<response::multiget_hashed>();

  typedef hash::request::get_hash hash_request;
  typedef std::unique_ptr<hash_request> hash_request_ptr;
  std::map<std::string, hash_request_ptr> hash_request_list;
  std::string value;

  for ( auto key : req->keys )
  {
    if ( _demo.get(key, &value) )
    {
      hash_request_list[key] = std::make_unique<hash_request>();
      hash_request_list[key]->value = value;   // в hash пойдёт value, не key
    }
    else
      (*presp)->values[key] = nullptr;         // сразу в ответ, get_hash не зовём
  }

  // Все ключи промахнулись — ответить можно сразу, цикл ниже пустой.
  if ( hash_request_list.empty() )
    cb( std::move(*presp) );

  // Сколько ответов hash ещё ждём. Последний успешный вызывает cb.
  auto psize = std::make_shared<size_t>( hash_request_list.size() );
  // recursive: вдруг hash ответит синхронно из того же потока, что и get_hash.
  auto pmutex = std::make_shared<std::recursive_mutex>();

  for (auto& req_hash: hash_request_list)
  {
    std::string key = req_hash.first;  // копия: req_hash сейчас move'им
    typedef hash::response::get_hash hash_response;

    _hash->get_hash( std::move(req_hash.second), this->callback([key, pmutex, psize, presp, cb](hash_response::ptr res_hash) mutable
    {
      // Пока держим lock, никто параллельно не пишет в presp / psize и не зовёт cb.
      std::unique_lock<std::recursive_mutex> lk(*pmutex);

      auto& ref_size = *psize;

      // Уже оборвали пачку (кто-то получил nullptr) — второй ответ слать нельзя.
      if ( ref_size == 0 )
        return;

      --(ref_size);

      if ( res_hash!=nullptr )
      {
        (*presp)->values[key] = std::make_shared<size_t>( res_hash->value );
        if ( ref_size == 0 )
        {
          // Это был последний hash — отдаём собранную карту.
          cb( std::move(*presp) );
        }
      }
      else
      {
        // Один hash упал — считаем весь запрос неудачным.
        ref_size = 0;
        cb( nullptr );
      }
    }));
  }
}

// multiget_hashed2: тот же fan-in, но ответ — vector<pair>, не map.
// Ненайденные ключи сразу кладём в values в порядке обхода.
// Найденные дописываются по мере прихода hash — их порядок = скорость соседа,
// а не порядок в запросе.

void demo_domain::multiget_hashed2( request::multiget_hashed2::ptr req, response::multiget_hashed2::handler cb)
{
  if ( this->notify_ban(req, cb) )
    return;

  if ( _hash==nullptr )
    return cb(nullptr);

  auto presp = std::make_shared<response::multiget_hashed2::ptr>();
  *presp = std::make_unique<response::multiget_hashed2>();

  typedef hash::request::get_hash hash_request;
  typedef std::unique_ptr<hash_request> hash_request_ptr;
  // vector, не map: сохраняем порядок, в котором нашли ключи у себя.
  std::vector< std::pair< std::string, hash_request_ptr > > hash_request_list;
  hash_request_list.reserve( req->keys.size() );
  std::string value;

  for ( auto key : req->keys )
  {
    if ( _demo.get(key, &value) )
    {
      hash_request_list.push_back( std::make_pair(key, std::make_unique<hash_request>() ) );
      hash_request_list.back().second->value = value;
    }
    else
      // Сразу в ответ, на том же месте в обходе запроса.
      (*presp)->values.push_back(std::make_pair(key, nullptr) );
  }

  if ( hash_request_list.empty() )
    cb( std::move(*presp) );

  auto psize = std::make_shared<size_t>( hash_request_list.size() );
  auto pmutex = std::make_shared<std::recursive_mutex>();

  for (auto& req_hash: hash_request_list)
  {
    std::string key = req_hash.first;
    typedef  hash::response::get_hash hash_response;

    _hash->get_hash( std::move(req_hash.second), this->callback([key, pmutex, psize, presp, cb](hash_response::ptr res_hash) mutable
    {
      std::unique_lock<std::recursive_mutex> lk(*pmutex);
      auto& ref_size = *psize;

      if ( ref_size == 0 )
        return;   // пачку уже оборвали

      --ref_size;

      if ( res_hash!=nullptr )
      {
        // push_back: эта пара окажется после «не найденных» и после тех hash,
        // что успели раньше. Итоговый порядок найденных — не детерминирован.
        (*presp)->values.push_back(std::make_pair(key, std::make_shared<size_t>( res_hash->value ) ) );
        if ( ref_size == 0 )
        {
          cb( std::move(*presp) );
        }
      }
      else
      {
        ref_size = 0;
        cb( nullptr );
      }
    }));
  }
}

}}
