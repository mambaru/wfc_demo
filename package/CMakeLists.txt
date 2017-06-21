include(BuildInfo)

SET(
  wfc_demo_source_list
  demo_package.cpp

  storage/storage_module.cpp
  storage/domain/storage_domain.cpp
  storage/domain/storage_multiton.cpp
  storage/service/storage_service_multiton.cpp
  storage/gateway/storage_gateway_multiton.cpp
  
  hash/domain/hash_domain.cpp
  hash/domain/hash_multiton.cpp
  hash/service/hash_service_multiton.cpp
  hash/gateway/hash_gateway_multiton.cpp
  hash/hash_module.cpp

  pingpong/pingpong_module.cpp
  pingpong/domain/pingpong_multiton.cpp
  pingpong/domain/pingpong.cpp
  pingpong/pinger/pinger_multiton.cpp
  pingpong/pinger/pinger.cpp
  pingpong/ponger/ponger_multiton.cpp
  pingpong/ponger/ponger.cpp
  pingpong/tank/tank_multiton.cpp
  pingpong/tank/tank.cpp
  pingpong/service/pingpong_service_multiton.cpp
  #pingpong/service/pinger_service_multiton.cpp
  pingpong/gateway/pingpong_gateway_multiton.cpp
)

add_library(
  wfc_demo
  ${wfc_demo_source_list}
)

add_dependencies(wfc_demo storage)
target_link_libraries(wfc_demo storage)

build_info(wfc_demo demo)

install(TARGETS wfc_demo DESTINATION ${CMAKE_INSTALL_PREFIX})
