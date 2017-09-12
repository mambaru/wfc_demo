#include <fas/testing.hpp>
#include <storage/storage.hpp>

struct _storage_;

UNIT(set, "")
{
  using namespace fas::testing;
  storage& stg = GET_REF(_storage_);
  stg.set("key1",  "+value1");
  stg.set("key99", "+value99");
  stg.set("keyX",  "+valueX");
  t << nothing;
}

UNIT(get, "")
{
  using namespace fas::testing;
  storage& stg = GET_REF(_storage_);
  std::string result;
  
  bool found = stg.get("key1", result);
  t << is_true<expect>(found) << " key1 not found." << FAS_FL;
  t << equal<expect>("+value1", result) << FAS_FL;

  found = stg.get("key99", result);
  t << is_true<expect>(found) << " key99 not found." << FAS_FL;
  t << equal<expect>("+value99", result) << FAS_FL;

  found = stg.get("keyX", result);
  t << is_true<expect>(found) << " keyX not found." << FAS_FL;
  t << equal<expect>("+valueX", result) << FAS_FL;

  found = stg.get("keyY", result);
  t << is_false<expect>(found) << " keyY is found." << FAS_FL;
  t << equal<expect, std::string>("", result) << FAS_FL;

}

UNIT(ini, "")
{
  using namespace fas::testing;
  storage& stg = GET_REF(_storage_);
  for (int i = 0; i < 100; ++i)
    stg.set("key"+std::to_string(i), "value"+std::to_string(i));
  for (int i = 0; i < 100; ++i)
  {
    std::string key = "key"+std::to_string(i);
    std::string value = "value"+std::to_string(i);
    std::string result;

    bool found = stg.get(key, result);
    t << is_true<expect>(found) << key << " not found." << FAS_FL;
    t << equal<expect>(value, result) << FAS_FL;
  }
}

BEGIN_SUITE(storage, "")
  ADD_UNIT( ini )
  ADD_UNIT( set )
  ADD_UNIT( get )
  ADD_VALUE(_storage_, storage)
END_SUITE(storage)
