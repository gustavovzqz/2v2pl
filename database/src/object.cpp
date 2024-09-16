#include "database/include/object.hpp"

Object::Object(char obj_name) : object_name_{obj_name} {

  object_lock_info_.fill(LockStatus::Open);
}


char Object::get_object_name() {
  return object_name_;
}


