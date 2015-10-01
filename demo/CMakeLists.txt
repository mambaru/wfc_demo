include(BuildInfo)

SET(
  wfc_demo_source_list
  demo_package.cpp
  module/demo_module.cpp

  module/demo_multiton.cpp
  module/demo_service_multiton.cpp
  module/demo_gateway_multiton.cpp

  module/pingpong_multiton.cpp
  module/pingpong_service_multiton.cpp
  module/pingpong_gateway_multiton.cpp

  demo/demo.cpp
  pingpong/pingpong.cpp
)

add_library(
  wfc_demo
  ${wfc_demo_source_list}
)

build_info(wfc_demo demo)

install(TARGETS wfc_demo DESTINATION ${CMAKE_INSTALL_PREFIX})
