#ifndef DATABASE_INCLUDE_OBJECT_HPP
#define DATABASE_INCLUDE_OBJECT_HPP

#include "object_lock_info.hpp" 

class Object {
  public:

  Object_lock_info obj_lock_info;

  virtual void blockFromBelow();
  virtual void blockFromAbove();
};

#endif
