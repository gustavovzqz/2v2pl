set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${PROJECT_ROOT_DIR}) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_subdirectory(parser)
add_subdirectory(database)
add_subdirectory(scheduler)
add_subdirectory(main)


