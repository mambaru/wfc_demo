cmake_minimum_required(VERSION 3.10)

project(wfc_demo VERSION "0.9.8")

include(cmake/ci.cmake)

wci_submodule(NAME wfc SUPERMODULE)

add_subdirectory(libdemostg)
add_subdirectory(package)

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
endif()

include(cmake/install.cmake)
