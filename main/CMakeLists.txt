project(main) 

add_executable(main main.cpp)
target_link_libraries(main scheduler parser)
