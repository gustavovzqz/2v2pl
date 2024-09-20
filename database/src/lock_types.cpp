#include "database/include/lock_types.hpp"
#include <cassert>
#include <stdexcept>


LockType get_intentional_from_lock(LockType lock_request) {
    switch(lock_request) {
        case WRITE_LOCK:
            return INTENTIONAL_WRITE_LOCK;
        case CERTIFY_LOCK:
            return INTENTIONAL_CERTIFY_LOCK;
        case UPDATE_LOCK:
            return INTENTIONAL_UPDATE_LOCK;
        case READ_LOCK:
            return INTENTIONAL_READ_LOCK;

        default:
            throw std::runtime_error("Esse objeto não possui intencional equivalente");
            break;
    }
}

std::vector<LockType> get_incompatible_locks(LockType lock_request){
    // Essa função só faz sentido ser chamada para os quatro principais.
    
    switch(lock_request) {
        case READ_LOCK:
            return {CERTIFY_LOCK, INTENTIONAL_CERTIFY_LOCK};
        case WRITE_LOCK:
            return {WRITE_LOCK, CERTIFY_LOCK, UPDATE_LOCK, INTENTIONAL_WRITE_LOCK, INTENTIONAL_UPDATE_LOCK, INTENTIONAL_CERTIFY_LOCK};
        case CERTIFY_LOCK:
            return {READ_LOCK, WRITE_LOCK, CERTIFY_LOCK, UPDATE_LOCK, INTENTIONAL_READ_LOCK, INTENTIONAL_WRITE_LOCK, INTENTIONAL_CERTIFY_LOCK, INTENTIONAL_UPDATE_LOCK};
        case UPDATE_LOCK: 
            return {WRITE_LOCK, CERTIFY_LOCK, UPDATE_LOCK, INTENTIONAL_WRITE_LOCK, INTENTIONAL_UPDATE_LOCK, INTENTIONAL_CERTIFY_LOCK};

        default:
            throw std::runtime_error("Não faz sentido chamar essa função para esse tipo de bloqueio (incompatible lock error");

    }

}
