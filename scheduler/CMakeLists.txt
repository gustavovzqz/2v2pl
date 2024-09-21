project(Scheduler)



include_directories(${Boost_INCLUDE_DIRS} include)

set(HEADERS
  "include/wait_graph.hpp"
  "include/scheduler.hpp"
)

set(SOURCES
  "src/wait_graph.cpp"
  "src/scheduler.cpp"
)

add_library(scheduler ${SOURCES} ${HEADERS})

target_link_libraries(scheduler database)
