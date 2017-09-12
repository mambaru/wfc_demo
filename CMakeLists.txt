cmake_minimum_required(VERSION 2.6)

project(wfc_demo)

include_directories(package)
include_directories(libstorage)

add_subdirectory(libstorage)
add_subdirectory(package)

