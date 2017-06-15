cmake_minimum_required(VERSION 2.6)

project(libstorage)

add_subdirectory(storage)

if ( BUILD_TESTING )
  add_subdirectory(tests)
endif()
