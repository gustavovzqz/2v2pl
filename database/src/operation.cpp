#include "database/include/operation.hpp"

Operation::Operation() {}

Operation::Operation(LockType lock_request, int transaction_id,
                     char object_name, std::string op_name)
    : lock_request(lock_request),
      transaction_id(transaction_id),
      object_name(object_name),
      operation_name{op_name} {}

LockType Operation::get_lock_request() { return lock_request; }

int Operation::get_transaction_id() const { return transaction_id; }

char Operation::get_object_name() { return object_name; }

std::string Operation::get_operation_name() { return operation_name; }
