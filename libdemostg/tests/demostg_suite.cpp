#include <fas/testing.hpp>
#include <demostg/demostg.hpp>

struct _storage_;

UNIT(set, "")
{
  using namespace fas::testing;
  demostg& stg = GET_REF(_storage_);
  t << is_false<expect>( stg.set("key1",  "+value1") ) << FAS_FL;
  t << is_false<expect>( stg.set("key99", "+value99") ) << FAS_FL;
  t << is_true<expect>( stg.set("keyX",  "+valueX") ) << FAS_FL;
}

UNIT(get, "")
{
  using namespace fas::testing;
  demostg& stg = GET_REF(_storage_);
  std::string result;
  
  bool found = stg.get("key1", &result);
  t << is_true<expect>(found) << " key1 not found." << FAS_FL;
  t << equal<expect, std::string>("value1", result) << FAS_FL;

  found = stg.get("key99", &result);
  t << is_true<expect>(found) << " key99 not found." << FAS_FL;
  t << equal<expect, std::string>("value99", result) << FAS_FL;

  found = stg.get("keyX", &result);
  t << is_true<expect>(found) << " keyX not found." << FAS_FL;
  t << equal<expect, std::string>("+valueX", result) << FAS_FL;

  found = stg.get("keyY", &result);
  t << is_false<expect>(found) << " keyY is found." << FAS_FL;
  // В result старое значение
  t << equal<expect, std::string>("+valueX", result) << FAS_FL;

}

UNIT(ini, "")
{
  using namespace fas::testing;
  demostg& stg = GET_REF(_storage_);
  for (int i = 0; i < 100; ++i)
    stg.set("key"+std::to_string(i), "value"+std::to_string(i));
  for (int i = 0; i < 100; ++i)
  {
    std::string key = "key"+std::to_string(i);
    std::string value = "value"+std::to_string(i);
    std::string result;

    bool found = stg.get(key, &result);
    t << is_true<expect>(found) << key << " not found." << FAS_FL;
    t << equal<expect>(value, result) << FAS_FL;
  }
}

BEGIN_SUITE(demostg, "")
  ADD_UNIT( ini )
  ADD_UNIT( set )
  ADD_UNIT( get )
  ADD_VALUE(_storage_, demostg)
END_SUITE(demostg)
