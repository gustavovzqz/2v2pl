project(Database)

set(HEADERS
  "include/database.hpp"
  "include/object.hpp"
  "include/transaction.hpp"
  "include/lock_types.hpp"
  "include/operation.hpp"
)

set(SOURCES
  "src/database.cpp"
  "src/object.cpp"
  "src/transaction.cpp"
  "src/lock_types.cpp"
  "src/operation.cpp"
)

add_library(database ${SOURCES} ${HEADERS})

