cmake_minimum_required(VERSION 3.1)

project(libstorage)

add_subdirectory(storage)

if ( BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
