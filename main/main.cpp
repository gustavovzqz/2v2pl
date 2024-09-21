#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <vector>

#include "database/include/database.hpp"
#include "database/include/operation.hpp"
#include "parser/include/parser.hpp"
#include "scheduler/include/scheduler.hpp"

int main() {
  Database banco_o{'o'};

  Tablespace tabela_m{'m', &banco_o};
  Tablespace tabela_n{'n', &banco_o};

  Page pagina_i{'i', &tabela_m};
  Page pagina_j{'j', &tabela_m};
  Page pagina_k{'k', &tabela_n};
  Page pagina_l{'l', &tabela_n};

  Tuple tupla_a{'a', &pagina_i};
  Tuple tupla_b{'b', &pagina_i};
  Tuple tupla_c{'c', &pagina_j};
  Tuple tupla_d{'d', &pagina_j};
  Tuple tupla_e{'e', &pagina_k};
  Tuple tupla_f{'f', &pagina_k};
  Tuple tupla_g{'g', &pagina_l};
  Tuple tupla_h{'h', &pagina_l};

  banco_o.add_tablespace(&tabela_m);
  banco_o.add_tablespace(&tabela_n);

  tabela_m.add_page(&pagina_i);
  tabela_m.add_page(&pagina_j);
  tabela_n.add_page(&pagina_k);
  tabela_n.add_page(&pagina_l);

  pagina_i.add_tuple(&tupla_a);
  pagina_i.add_tuple(&tupla_b);
  pagina_j.add_tuple(&tupla_c);
  pagina_j.add_tuple(&tupla_d);
  pagina_k.add_tuple(&tupla_e);
  pagina_k.add_tuple(&tupla_f);
  pagina_l.add_tuple(&tupla_g);
  pagina_l.add_tuple(&tupla_h);

  std::map<char, Object *> name_to_object_map =
      get_object_map({&banco_o, &tabela_m, &tabela_n, &pagina_i, &pagina_j,
                      &pagina_k, &pagina_l, &tupla_a, &tupla_b, &tupla_c,
                      &tupla_d, &tupla_e, &tupla_f, &tupla_g, &tupla_h});

  Parser parser{};

  std::string input_string;
  std::cout << "Enter operations: ";
  std::getline(std::cin, input_string);

  std::vector<std::string> input = split_by_space(input_string);

  parser.parse_operations(input);

  std::vector<Transaction *> transactions_ptr;

  for (Transaction &tr : parser.transaction_list_) {
    transactions_ptr.push_back(&tr);
  }

  Scheduler escalonador{parser.operation_list_, transactions_ptr,
                        name_to_object_map};

  std::list<Operation> output_schedule = escalonador.get_2v2pl_schedule();

  for (Operation op : output_schedule) {
    std::cout << op.get_operation_name() << ' ';
  }

  std::cout << std::endl;

  return 0;
}
