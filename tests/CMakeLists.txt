set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${UNIT_TEST_BIN_OUTPUT_DIR})

add_executable(demo_test demo_test.cpp demo_suite.cpp ${FAS_TESTING_CPP})

add_test(NAME demo_test COMMAND demo_test)

target_link_libraries(demo_test wfc_demo )

