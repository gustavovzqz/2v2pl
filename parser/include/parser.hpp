#ifndef PARSER_INCLUDE_PARSER_HPP
#define PARSER_INCLUDE_PARSER_HPP

#include <list>
#include <sstream>
#include <vector>

#include "database/include/operation.hpp"
#include "database/include/transaction.hpp"

struct Parser {
  std::vector<std::string> get_input();
  void parse_operations(std::vector<std::string> input);

  std::list<Operation> operation_list_;
  std::vector<Transaction> transaction_list_;
};

std::vector<std::string> split_by_space(const std::string &str);

#endif
