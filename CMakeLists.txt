cmake_minimum_required(VERSION 2.6)

project(wfc_demo)

if ( NOT WFC_READY )
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/wfc/cmake")
  include(Wfc)
endif()

include(Wfc)

include_directories(./demo)

add_subdirectory(demo)

if ( WFC_BUILD_ALL || DEMO_BUILD_ALL )
  add_subdirectory(tests)
endif()
