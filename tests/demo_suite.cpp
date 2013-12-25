#include <fas/testing.hpp>

UNIT(set, "")
{
  t << fas::testing::nothing();
}

UNIT(get, "")
{
  t << fas::testing::nothing();
}

UNIT(reverse, "")
{
  t << fas::testing::nothing();
}

UNIT(generate, "")
{
  t << fas::testing::nothing();
}

BEGIN_SUITE(demo_suite, "")
  ADD_UNIT( set )
  ADD_UNIT( get )
  ADD_UNIT( reverse )
  ADD_UNIT( generate )
END_SUITE(demo_suite)
