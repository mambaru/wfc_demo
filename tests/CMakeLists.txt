
SET(
  demo_test_source_list
  demo_suite.cpp
  demo_test.cpp
  ${FAS_TESTING_CPP}
)

add_executable(
  demo_test
  ${demo_test_source_list}
)

add_test(demo_test demo_test)


