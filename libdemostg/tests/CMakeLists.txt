add_executable(demostg_test demostg_suite.cpp demostg_test.cpp)
add_dependencies(demostg_test demostg)

target_link_libraries(demostg_test PRIVATE demostg fas::testing)

wci_test(TARGET demostg_test COMMAND demostg_test )


