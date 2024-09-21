#ifndef INCLUDE_DATABASE_LOCK_TYPES_HPP
#define INCLUDE_DATABASE_LOCK_TYPES_HPP

#include <cassert>
#include <cstdint>
#include <vector>

enum LockType : uint8_t {
  READ_LOCK = 0,
  WRITE_LOCK = 1,
  CERTIFY_LOCK = 2,
  UPDATE_LOCK = 3,
  INTENTIONAL_READ_LOCK = 4,
  INTENTIONAL_WRITE_LOCK = 5,
  INTENTIONAL_CERTIFY_LOCK = 6,
  INTENTIONAL_UPDATE_LOCK = 7,
};

LockType get_intentional_from_lock(LockType lock_request);
std::vector<LockType> get_incompatible_locks(LockType lock_request);

#endif
