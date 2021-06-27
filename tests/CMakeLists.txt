add_executable(demo_test demo_test.cpp demo_suite.cpp package_suite.cpp)
target_link_libraries(demo_test PRIVATE wfc_demo fas::testing)
wci_test(TARGET demo_test COMMAND demo_test)


