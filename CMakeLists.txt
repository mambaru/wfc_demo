cmake_minimum_required(VERSION 3.1)

project(wfc_demo)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ci)

if ( STANDALONE )
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/wfc/cmake)
  getlibs(faslib wjson wlog wflow iow wjrpc wrtstat wfc)
  enable_testing()
else()
  set(BUILD_TESTING OFF)
endif()

include_directories(package)
include_directories(libstorage)

add_subdirectory(libstorage)
add_subdirectory(package)

if ( STANDALONE AND BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
endif()
