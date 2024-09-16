project(Scheduler)

set(HEADERS
  "include/wait_graph.hpp"
  "include/scheduler.hpp"
)

SET(SOURCES
  "src/wait_graph.cpp"
  "src/scheduler.cpp"
)

add_library(scheduler ${SOURCES} ${HEADERS})
