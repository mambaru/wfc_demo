
SET(
  demo_source_list
  demo.cpp
  demo_storage.cpp
)

add_library(
  demo SHARED
  ${demo_source_list}
)

