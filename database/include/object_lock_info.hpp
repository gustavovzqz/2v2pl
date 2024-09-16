#ifndef DATABASE_INCLUDE_OBJECT_LOCK_INFO_HPP
#define DATABASE_INCLUDE_OBJECT_LOCK_INFO_HPP

#include <vector>

struct Object_lock_info {
  Object_lock_info();
  std::vector<bool> lock_info;

};

#endif
