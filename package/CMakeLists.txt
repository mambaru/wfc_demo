include(BuildInfo)

SET(
  wfc_demo_source_list
  demo_package.cpp

  storage/storage_module.cpp
  storage/storage_multiton.cpp
  storage/service/storage_service_multiton.cpp
  storage/gateway/storage_gateway_multiton.cpp
  storage/storage.cpp

  hash/hash_module.cpp
  hash/hash_multiton.cpp
  hash/service/hash_service_multiton.cpp
  hash/gateway/hash_gateway_multiton.cpp
  hash/hash.cpp

  pingpong/pingpong_module.cpp
  pingpong/domain/pingpong_multiton.cpp
  pingpong/domain/pingpong.cpp
  pingpong/tank/tank_multiton.cpp
  pingpong/tank/tank.cpp
  pingpong/service/pingpong_service_multiton.cpp
  pingpong/gateway/pingpong_gateway_multiton.cpp
 
)

add_library(
  wfc_demo
  ${wfc_demo_source_list}
)

build_info(wfc_demo demo)

install(TARGETS wfc_demo DESTINATION ${CMAKE_INSTALL_PREFIX})
