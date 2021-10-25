
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
wci_targets(wfc_demo)
enable_stat(wfc_demo)
add_dependencies(wfc_demo storage)

target_link_libraries(wfc_demo PUBLIC wfc PRIVATE storage )

target_include_directories(wfc_demo PUBLIC ${wfc_demo_SOURCE_DIR})
target_include_directories(wfc_demo PUBLIC ${wfc_demo_SOURCE_DIR}/package)
target_include_directories(wfc_demo PUBLIC ${wfc_demo_SOURCE_DIR}/libstorage)

build_info(wfc_demo demo)

install(TARGETS wfc_demo DESTINATION ${CMAKE_INSTALL_PREFIX})
