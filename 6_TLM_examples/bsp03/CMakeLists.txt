include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../bsp02)

add_executable(k6b3
  k6b3.cpp
)

target_link_libraries(k6b3
                               systemc
                               m)

