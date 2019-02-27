cmake_minimum_required(VERSION 3.1)

project(wfc_demo)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ci)
wfc_package()

include_directories(package)
include_directories(libstorage)

add_subdirectory(libstorage)
add_subdirectory(package)

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
endif()
