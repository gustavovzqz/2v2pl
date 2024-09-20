#include "database/include/object.hpp"
#include "database/include/lock_types.hpp"
#include <iostream>


Object::Object(char obj_name) : object_name_{obj_name} {}


char Object::get_object_name() {
  return object_name_;
}


std::unordered_set<int> Object::get_pending_transactions(int transaction_id, LockType lock_request) {
    std::vector<LockType> incompatible_locks{get_incompatible_locks(lock_request)};
    std::unordered_set<int> pending_transactions; 

    for (auto lock : incompatible_locks) {
        const auto& transactions = object_lock_info_[lock];
        pending_transactions.insert(transactions.begin(), transactions.end());
    }

    pending_transactions.erase(transaction_id);

    return pending_transactions; 
}


std::unordered_set<int> Object::upgrade_write_to_certify(int transaction_id) {
    std::unordered_set<int> pending_vector; 

    for (const auto& pending_transactions : object_lock_info_) {
        for (const auto& trans_id : pending_transactions) {
            if (trans_id != transaction_id) {
                pending_vector.insert(trans_id); 
            }
        }
    }

    if (pending_vector.empty()) {
    object_lock_info_[WRITE_LOCK].erase(transaction_id); 
    object_lock_info_[CERTIFY_LOCK].insert(transaction_id);
  }

    return pending_vector; 
}

void Object::abort_transaction(int id) {
    for (auto& pending_transactions : object_lock_info_) {
        pending_transactions.erase(id);
    }
}


void Object::print_lock_info() {
    for (size_t i = 0; i < object_lock_info_.size(); ++i) {
        std::cout << "Lock type " << i << ": ";
        const auto& pending_transactions = object_lock_info_[i];

        if (pending_transactions.empty()) {
            std::cout << "No pending transactions." << std::endl;
        } else {
            std::cout << "Pending transactions: ";
            for (const auto& trans_id : pending_transactions) {
                std::cout << trans_id << " ";
            }
            std::cout << std::endl;
        }
    }
}