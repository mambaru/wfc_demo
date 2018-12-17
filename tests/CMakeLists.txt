enable_testing()

add_executable(demo_test demo_test.cpp demo_suite.cpp ${FAS_TESTING_CPP})
add_test(demo_test demo_test)
target_link_libraries(demo_test wfc_demo )

