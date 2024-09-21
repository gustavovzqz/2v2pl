#ifndef DATABASE_INCLUDE_OPERATION_HPP
#define DATABASE_INCLUDE_OPERATION_HPP

#include <string>

#include "lock_types.hpp"

class Operation {
  LockType lock_request;  // W
  int transaction_id;     // 1 -> c1(-)
  char object_name;       // (x)
  std::string operation_name;

 public:
  Operation();
  Operation(LockType lock_request, int transaction_id, char object_name,
            std::string operation_name);
  LockType get_lock_request();
  int get_transaction_id() const;
  char get_object_name();
  std::string get_operation_name();
};

#endif