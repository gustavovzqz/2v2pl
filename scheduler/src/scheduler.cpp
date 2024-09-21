#include "scheduler/include/scheduler.hpp"

#include <fstream>

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

  std::ofstream output_file("schedule_output.txt");
  if (!output_file) {
    std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
    return output_schedule;
  }

  output_file << "Início do agendamento..." << std::endl;

  while (!operations_.empty() || !waiting_operations.empty()) {
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

    if (!choosed_by_waiting) {
      current_op = operations_.front();
      operations_.pop_front();
    }

    output_file << "Operação escolhida: " << current_op.get_operation_name()
                << std::endl;

    char object_name = current_op.get_object_name();
    int transaction_id = current_op.get_transaction_id();
    Transaction* current_transaction = transactions_[transaction_id];
    LockType lock_request = current_op.get_lock_request();

    if (wait_graph.is_waiting(transaction_id)) {
      waiting_operations.push_back(current_op);
      output_file << "Operação " << current_op.get_operation_name()
                  << " está aguardando." << std::endl;
      continue;
    }

    if (lock_request == CERTIFY_LOCK) {
      auto pending_transactions =
          current_transaction->upgrade_write_to_certify();
      if (!pending_transactions.empty()) {
        waiting_operations.push_back(current_op);
        output_file << "Operação " << current_op.get_operation_name()
                    << " está aguardando devido a um bloqueio." << std::endl;

        for (int pending_transaction_id : pending_transactions) {
          wait_graph.add_edge(transaction_id, pending_transaction_id);
        }

        if (wait_graph.has_cycles()) {
          output_file << "Ciclo detectado envolvendo transação "
                      << transaction_id << std::endl;
          current_transaction->abort();
          output_file << "Transação " << transaction_id << " abortada."
                      << std::endl;
          wait_graph.remove_node(transaction_id);
          clean_list(waiting_operations, transaction_id);
          clean_list(operations_, transaction_id);
          clean_list(output_schedule, transaction_id);
        }
      } else {
        output_file << "Adicionando ao schedule de saída\n";
        current_transaction->abort();
        output_schedule.push_back(current_op);
        wait_graph.remove_node(transaction_id);
      }
    } else {
      Object* object_to_block = object_map_[object_name];
      auto pending_transactions =
          object_to_block->get_incompatible_transactions(transaction_id,
                                                         lock_request);

      if (pending_transactions.empty()) {
        object_to_block->block(current_transaction, lock_request);
        output_file << "Bloqueio concedido para transação " << transaction_id
                    << " em " << object_name << std::endl;
        output_file << "Adicionando ao schedule de saída\n";

        output_schedule.push_back(current_op);
      } else {
        waiting_operations.push_back(current_op);
        output_file << "Operação " << current_op.get_operation_name()
                    << " está aguardando." << std::endl;

        for (int pending_transaction_id : pending_transactions) {
          wait_graph.add_edge(transaction_id, pending_transaction_id);
        }

        if (wait_graph.has_cycles()) {
          output_file << "Ciclo detectado!";
          current_transaction->abort();
          output_file << "Transação " << transaction_id << " abortada."
                      << std::endl;
          wait_graph.remove_node(transaction_id);
          clean_list(waiting_operations, transaction_id);
          clean_list(operations_, transaction_id);
          clean_list(output_schedule, transaction_id);
        }
      }
    }
  }

  output_file << "Todas as operações foram processadas." << std::endl;
  output_file.close();
  return output_schedule;
}
