project(Database)

set(HEADERS
  "include/database.hpp"
  "include/object.hpp"
  "include/transaction.hpp"
  "include/uids.hpp"
)

set(SOURCES
  "src/database.cpp"
  "src/object.cpp"
  "src/transaction.cpp"
)

add_library(database ${SOURCES} ${HEADERS})

