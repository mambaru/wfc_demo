cmake_minimum_required(VERSION 2.6)

project(wfc_demo)

include_directories(package)

add_subdirectory(package)

if ( WFC_BUILD_ALL OR DEMO_BUILD_ALL )
  add_subdirectory(tests)
endif()
