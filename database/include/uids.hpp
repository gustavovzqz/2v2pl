#ifndef INCLUDE_DATABASE_UIDS_HPP
#define INCLUDE_DATABASE_UIDS_HPP

#include <cstdint>


enum LockType : uint8_t {
    READ_LOCK = 1,
    WRITE_LOCK = 2,
    CERTIFY_LOCK = 3,
    UPDATE_LOCK = 4,
    INTENTIONAL_READ_LOCK = 5,
    INTENTIONAL_WRITE_LOCK = 6,
    INTENTIONAL_UPDATE_LOCK = 7
};

#endif
