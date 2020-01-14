add_executable(storage_test storage_suite.cpp storage_test.cpp)
add_dependencies(storage_test storage)
target_link_libraries(storage_test PRIVATE storage fas::testing)
wci_test(TARGET storage_test COMMAND storage_test )


