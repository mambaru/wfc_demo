include(BuildInfo)

SET(
  wfc_demo_source_list
  demo_package.cpp

  demo/demo_module.cpp
  demo/domain/demo_domain.cpp
  demo/domain/demo_multiton.cpp
  demo/service/demo_service_multiton.cpp
  demo/gateway/demo_gateway_multiton.cpp
  
  hash/domain/hash_domain.cpp
  hash/domain/hash_multiton.cpp
  hash/service/hash_service_multiton.cpp
  hash/gateway/hash_gateway_multiton.cpp
  hash/hash_module.cpp
  
  pingpong/pinger/pinger.cpp
  pingpong/pinger/pinger_multiton.cpp
  pingpong/pinger_service/pinger_service_multiton.cpp
  pingpong/pinger_gateway/pinger_gateway_multiton.cpp
  
  pingpong/ponger/ponger.cpp
  pingpong/ponger/ponger_multiton.cpp
  pingpong/ponger_service/ponger_service_multiton.cpp
  pingpong/ponger_gateway/ponger_gateway_multiton.cpp
  
  pingpong/tank/tank.cpp
  pingpong/tank/tank_multiton.cpp
  pingpong/pingpong_module.cpp
)

add_library(wfc_demo ${wfc_demo_source_list})

add_dependencies(wfc_demo storage)
target_link_libraries(wfc_demo storage ${WFC_LIBRARIES})

build_info(wfc_demo demo)

install(TARGETS wfc_demo DESTINATION ${CMAKE_INSTALL_PREFIX})
