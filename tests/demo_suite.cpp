#include <fas/testing.hpp>
#include <demo/domain/demo_domain.hpp>
#include <hash/domain/hash_domain.hpp>
#include <wfc/testing/testing_domain.hpp>

UNIT(demo1, "")
{
  using namespace fas::testing;
  using namespace damba;
  t << nothing;

  auto ptest = std::make_shared<wfc::testing_domain>();
  demo::demo_domain::domain_config conf;
  conf.name = "demo1";
  conf.hash_target = "hash1";

  auto pdemo = ptest->create<demo::demo_domain>(conf);

  auto set=std::make_unique<demo::request::set>();
  set->key="key1";
  set->value="val1";
  pdemo->set(std::move(set), [&t](demo::response::set::ptr res){
    using namespace fas::testing;
    t << is_true<expect>(res->status) << FAS_FL;
  });

  auto get=std::make_unique<demo::request::get>();
  get->key="key1";
  pdemo->get(std::move(get), [&t](demo::response::get::ptr res){
    using namespace fas::testing;
    t << equal<expect>(res->value, "val1") << FAS_FL;
  });

  auto get_hashed=std::make_unique<demo::request::get_hashed>();
  get_hashed->key="key1";
  pdemo->get_hashed(std::move(get_hashed), [&t](demo::response::get_hashed::ptr res){
    using namespace fas::testing;
    t << equal<assert>(res, nullptr) << FAS_FL;
  });

  hash::hash_domain::domain_config hash_conf;
  hash_conf.name = "hash1";
  auto phash = ptest->create<hash::hash_domain>(hash_conf);
  ptest->initialize();

  get_hashed=std::make_unique<demo::request::get_hashed>();
  get_hashed->key="key1";
  pdemo->get_hashed(std::move(get_hashed), [&t](demo::response::get_hashed::ptr res){
    using namespace fas::testing;

    t << not_equal<assert, demo::response::get_hashed::ptr>(res, nullptr) << FAS_FL;
    t << stop;
    t << not_equal<assert, size_t>(res->value, std::hash<std::string>()("key1") ) << FAS_FL;
    t << equal<assert>(res->value, std::hash<std::string>()("val1") ) << FAS_FL;
  });

  ptest->stop();
  pdemo->stop();
  phash->stop();

  ptest.reset();
  pdemo.reset();
  phash.reset();

}

BEGIN_SUITE(demo, "")
  ADD_UNIT(demo1)
END_SUITE(demo)
