project(Parser)

set(HEADERS
  "include/parser.hpp"
)

SET(SOURCES
  "src/parser.cpp"
)

add_library(parser ${SOURCES} ${HEADERS})

target_link_libraries(parser database)