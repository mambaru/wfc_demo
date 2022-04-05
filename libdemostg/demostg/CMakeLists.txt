
add_library(demostg demostg.cpp)

target_include_directories(demostg PUBLIC ${libdemostg_SOURCE_DIR})

wci_targets(demostg)
