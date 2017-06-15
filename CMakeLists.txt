cmake_minimum_required(VERSION 2.6)

project(wfc_demo)

include_directories(package)
include_directories(libstorage)

add_subdirectory(libstorage)
add_subdirectory(package)

if ( WFC_BUILD_ALL OR DEMO_BUILD_ALL )
  add_subdirectory(tests)
endif()
