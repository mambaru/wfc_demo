cmake_minimum_required(VERSION 3.1)

project(wfc_demo)

include(cmake/ci.cmake)
wfc_libs()

include_directories(package)
include_directories(libstorage)

add_subdirectory(libstorage)
add_subdirectory(package)

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
endif()
