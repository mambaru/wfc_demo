cmake_minimum_required(VERSION 2.6)

project(wfc_demo)

if ( NOT WFC_READY )
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/wfc/cmake")
  include(Wfc)
endif()

include(Wfc)

include_directories(wfc)
include_directories(.)

add_subdirectory(demo)
add_subdirectory(hash)
add_subdirectory(module)
