
include(BuildInfo)

SET(
  wfc_demo_source_list
  demo_package.cpp
  demo_module.cpp
  demo_object.cpp
  domain/demo_domain.cpp
)

add_library(
  wfc_demo
  ${wfc_demo_source_list}
)

build_info(wfc_demo demo)

install(TARGETS wfc_demo DESTINATION ${CMAKE_INSTALL_PREFIX})
