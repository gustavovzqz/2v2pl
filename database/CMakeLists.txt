project(Database)

set(HEADERS
  "include/database.hpp"
  "include/object.hpp"
  "include/object_lock_info.hpp"
  "include/transaction.hpp"
  "include/uids.hpp"
)

set(SOURCES
  "src/database.cpp"
  "src/object.cpp"
  "src/transaction.cpp"
  "src/object_lock_info.cpp"
)

add_library(database ${SOURCES} ${HEADERS})

