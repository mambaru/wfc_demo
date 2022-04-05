cmake_minimum_required(VERSION 3.1)

project(libdemostg)

add_subdirectory(demostg)

if ( BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
