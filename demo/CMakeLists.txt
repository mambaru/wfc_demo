message(STATUS "MODULE PATH: ${CMAKE_MODULE_PATH}")


include(BuildInfo)

SET(
  wfc_demo_source_list
  demo_instance.cpp
  demo.cpp
  server_tcp.cpp
)

add_library(
  wfc_demo SHARED
  ${wfc_demo_source_list}
)

build_info(wfc_demo demo)

