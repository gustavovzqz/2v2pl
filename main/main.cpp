#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "database/include/database.hpp"
#include "database/include/operation.hpp"
#include "scheduler/include/scheduler.hpp"

int main() {
  Database banco{'X'};
  Tablespace tabela{'A', &banco};
  Page pagina{'B', &tabela};
  Tuple tupla{'C', &pagina};

  banco.add_tablespace(&tabela);
  tabela.add_page(&pagina);
  pagina.add_tuple(&tupla);

  Transaction T0{0};
  Transaction T1{1};

  Operation r0x{READ_LOCK, 0, 'X', "r0(x)"};
  Operation c0{CERTIFY_LOCK, 0, '-', "c0"};

  Operation r1x{READ_LOCK, 1, 'X', "r1(x)"};
  Operation c1{CERTIFY_LOCK, 1, '-', "c1"};

  std::list<Operation> operations = {r0x, r1x, c1, c0};
  std::vector<Transaction*> transactions = {&T0, &T1};

  std::map<char, Object*> name_to_object_map;
  name_to_object_map['X'] = &banco;
  name_to_object_map['A'] = &tabela;
  name_to_object_map['B'] = &pagina;
  name_to_object_map['C'] = &tupla;

  Scheduler scheduler{operations, transactions, name_to_object_map};

  std::list<Operation> schedule = scheduler.get_2v2pl_schedule();

  std::cout << "\n--------------------\n";

  for (auto operation : schedule) {
    std::cout << operation.get_operation_name() << std::endl;
  }

  return 0;
}
