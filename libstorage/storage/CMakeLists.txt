add_library(storage storage.cpp)
target_include_directories(storage PUBLIC ${libstorage_SOURCE_DIR})
wci_targets(storage)
