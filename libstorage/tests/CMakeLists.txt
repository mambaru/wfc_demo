set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${WFC_TEST_DIR})

SET(
  storage_test_source_list
    storage_suite.cpp
    storage_test.cpp
    ${FAS_TESTING_CPP}
)

add_executable(
  storage_test
  ${storage_test_source_list}
)

add_dependencies(storage_test storage)

target_link_libraries(storage_test storage)

add_test(NAME storage_test COMMAND storage_test WORKING_DIRECTORY ${WFC_TEST_DIR} )


