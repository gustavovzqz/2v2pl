#include "database/include/transaction.hpp"
#include "database/include/object.hpp"
#include <unordered_set> 
#include <algorithm>


Transaction::Transaction(int id) : transaction_id_{id} {}


// Retorna uma lista de transações pendentes para o pedido de bloqueio.
std::unordered_set<int> Transaction::upgrade_write_to_certify() {
    std::unordered_set<int> pending_transactions; 

    for (auto* object : objects_) {
        const auto& pending = object->upgrade_write_to_certify(transaction_id_);
        
        pending_transactions.insert(pending.begin(), pending.end());
    }

    return pending_transactions; 
}

void Transaction::push_object_info(Object* block_info) {

    // Caso não tenha o ponteiro para o objeto no vetor, adiciona.
    if (std::find(objects_.begin(), objects_.end(), block_info) == objects_.end()) {
        objects_.push_back(block_info);
    }
}


int Transaction::get_id() {
  return transaction_id_;
}

void Transaction::abort(){
    
    for (auto* object : objects_) {
            object->abort_transaction(transaction_id_);
    }

}
