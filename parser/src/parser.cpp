#include "parser/include/parser.hpp"

#include <iostream>

using std::string;

std::vector<std::string> Parser::get_input() {
  std::vector<std::string> inputs;
  std::cout << "Write your operations. Empty to stop." << std::endl;

  std::string curr_input;

  while (true) {
    std::getline(std::cin, curr_input);

    if (curr_input.empty()) {
      break;
    }

    inputs.push_back(curr_input);
  }

  return inputs;
}

// r1(x)
// c1

LockType get_lock_by_symbol(char symbol) {
  switch (symbol) {
    case 'r':
      return READ_LOCK;
    case 'w':
      return WRITE_LOCK;
    case 'u':
      return UPDATE_LOCK;
    default:
      throw std::runtime_error("nao chama a função pra esse simbolo caba!");
  }
}

void Parser::parse_operations(std::vector<string> inputs) {
  int max_transaction_id = 0;
  for (string& input : inputs) {
    int size = input.size();
    int transaction_id{0};

    if (size == 2) {
      transaction_id = (input[1] - '0');

      Operation new_operation{CERTIFY_LOCK, transaction_id, '-', input};
      operation_list_.push_back(new_operation);

    } else if (size == 5) {
      char operation_symbol = input[0];
      transaction_id = ((input[1]) - '0');

      char object_name = input[3];
      LockType lock_value = get_lock_by_symbol(operation_symbol);

      Operation new_operation{lock_value, transaction_id, object_name, input};
      operation_list_.push_back(new_operation);

    } else {
      throw std::runtime_error("Elemento inválido para o parser!");
    }

    if (transaction_id > max_transaction_id) {
      max_transaction_id = transaction_id;
    }
  }

  for (auto i = 0; i <= max_transaction_id; ++i) {
    Transaction new_transaction{i};
    transaction_list_.push_back(new_transaction);
  }
}

std::vector<std::string> split_by_space(const std::string& str) {
  std::vector<std::string> result;
  std::istringstream iss(str);
  std::string item;

  while (iss >> item) {
    result.push_back(item);
  }

  return result;
}