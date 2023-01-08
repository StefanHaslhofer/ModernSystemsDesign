add_executable(k6b2
  k6b2.cpp
)

add_executable(k6b2_simple
  k6b2_simple.cpp
)

target_link_libraries(k6b2 systemc m)
                               
target_link_libraries(k6b2_simple systemc m)
