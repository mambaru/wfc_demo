
add_library(demostg demostg.cpp)

target_include_directories(demostg PUBLIC $<BUILD_INTERFACE:${demostg_SOURCE_DIR}>)

wci_targets(demostg)
