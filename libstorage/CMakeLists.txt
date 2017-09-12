cmake_minimum_required(VERSION 2.6)

project(libstorage)

add_subdirectory(storage)

if ( BUILD_TESTING OR DEMO_BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
endif()
