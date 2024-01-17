cmake_minimum_required(VERSION 3.10)

project(demostg VERSION "0.9.8")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

include(cmake/ci)

add_subdirectory(demostg)

if ( BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

include(cmake/install)
