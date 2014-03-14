message(STATUS "MODULE PATH: ${CMAKE_MODULE_PATH}")

include(BuildInfo)

include_directories(.)

SET(
  wfc_demo_source_list
  demo_instance.cpp
  #service/server_tcp.cpp
  domain/domain.cpp
)

add_library(
  wfc_demo SHARED
  ${wfc_demo_source_list}
)

build_info(wfc_demo demo)

