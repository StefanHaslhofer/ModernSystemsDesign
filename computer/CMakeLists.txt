# add the executable
add_executable(computer src/main.cpp
                            src/computer.cpp
                            src/cloudServer.cpp
                            src/cloud.cpp)            
# include headers and link SystemC
target_include_directories(computer PRIVATE inc)
target_link_libraries(computer systemc)
