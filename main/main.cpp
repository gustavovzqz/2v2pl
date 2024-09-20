#include "database/include/database.hpp"
#include <iostream>


int main() {
  Database banco{'X'}; 

  Tablespace tabela{'A', &banco};

  Page pagina{'B', &tabela}; 

  Tuple tupla{'C', &pagina};

  Transaction T1{0};
  Transaction T2{1};


  tupla.block(T1, WRITE_LOCK);
  tupla.block(T2, WRITE_LOCK);

  tupla.print_lock_info();

  std::cout << "Fezes\n";

  T1.abort();
  T2.abort();

  tupla.print_lock_info();

  

}

