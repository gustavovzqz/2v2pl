#include "scheduler/include/scheduler.hpp"

#include <iostream>

#include "scheduler/include/wait_graph.hpp"

Scheduler::Scheduler(std::list<Operation> operations,
                     std::vector<Transaction*> transactions,
                     std::map<char, Object*> object_map)
    : operations_{operations},
      transactions_{transactions},
      object_map_{object_map} {}

void clean_list(std::list<Operation>& operations, int transaction_id) {
  operations.remove_if([transaction_id](const Operation& op) {
    return op.get_transaction_id() == transaction_id;
  });
}

std::list<Operation> Scheduler::get_2v2pl_schedule() {
  WaitGraph wait_graph{static_cast<int>(transactions_.size())};
  std::list<Operation> waiting_operations;
  std::list<Operation> output_schedule;

  while (!operations_.empty() || !waiting_operations.empty()) {
    // Primeiro percorremos a fila das que estão aguardando e vemos se alguma
    // pode ser escalonada.

    Operation current_op;

    bool choosed_by_waiting{false};

    for (auto op = waiting_operations.begin();
         op != waiting_operations.end();) {
      if (!wait_graph.is_waiting(op->get_transaction_id())) {
        current_op = *op;
        op = waiting_operations.erase(op);
        choosed_by_waiting = true;
        break;

      } else {
        ++op;
      }
    }

    // Se não tinha disponível na lista de espera, eu pega na normal
    if (!choosed_by_waiting) {
      current_op = operations_.front();
      operations_.pop_front();
    }

    std::cout << "Operação escolhida: " << current_op.get_operation_name()
              << std::endl;
    char object_name = current_op.get_object_name();
    int transaction_id = current_op.get_transaction_id();
    Transaction* current_transaction = transactions_[transaction_id];
    LockType lock_request = current_op.get_lock_request();

    // 1. A transação está esperando.

    if (wait_graph.is_waiting(transaction_id)) {
      waiting_operations.push_back(current_op);
      continue;
      // Pula essa iteração e vai para a próxima
    }

    // 2. A transação não está esperando.

    // 2.1 A operação é de commit? (pede um certify lock?)

    if (lock_request == CERTIFY_LOCK) {
      // Tenta fazer o upgrade
      auto pending_transactions =
          current_transaction->upgrade_write_to_certify();
      if (!pending_transactions.empty()) {
        std::cout << "Entrou aqui!\n";
        waiting_operations.push_back(current_op);

        for (int pending_transaction_id : pending_transactions) {
          wait_graph.add_edge(transaction_id, pending_transaction_id);
        }

        if (wait_graph.has_cycles()) {
          std::cout << "Formou ciclo\n";
          current_transaction->abort();
          wait_graph.remove_node(transaction_id);

          // Limpa as filas de transação (saida, espera e entrada) removendo os
          // ids das transações abortadas
          clean_list(waiting_operations, transaction_id);
          clean_list(operations_, transaction_id);
          clean_list(output_schedule, transaction_id);
        }

        // Conseguiu fazer o upgrade do write para certify
      } else {
        std::cout << "Adicionando ao schedule de saída\n";
        current_transaction->abort();
        output_schedule.push_back(current_op);
        wait_graph.remove_node(transaction_id);
      }

    } else {
      // 2.2 A operação NÃO é de commit.

      // Casos para READ, WRITE e UPDATE

      Object* object_to_block = object_map_[object_name];

      auto pending_transactions =
          object_to_block->get_incompatible_transactions(transaction_id,
                                                         lock_request);

      if (pending_transactions.empty()) {
        // Concede o bloqueio

        object_to_block->block(current_transaction, lock_request);
        std::cout << "Adicionando ao schedule de saida\n";
        output_schedule.push_back(current_op);

      } else {
        waiting_operations.push_back(current_op);

        for (int pending_transaction_id : pending_transactions) {
          wait_graph.add_edge(transaction_id, pending_transaction_id);
        }

        if (wait_graph.has_cycles()) {
          std::cout << "Formou ciclo!";
          current_transaction->abort();
          wait_graph.remove_node(transaction_id);

          // Limpa as filas de transação (saida, espera e entrada) removendo os
          // ids das transações abortadas
          clean_list(waiting_operations, transaction_id);
          clean_list(operations_, transaction_id);
          clean_list(output_schedule, transaction_id);
        }
      }
    }
  }
  return output_schedule;
}
