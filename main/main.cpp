#include "database/include/database.hpp"
#include <iostream>


int main() {
  Database banco{'X'}; 
  Tablespace tabela{'A', &banco};
  Page pagina{'B', &tabela}; 
  Tuple tupla{'C', &pagina};

  banco.add_tablespace(&tabela);
  tabela.add_page(&pagina);
  pagina.add_tuple(&tupla);

  

  Transaction T1{0};


  banco.block(T1, WRITE_LOCK);

  auto x = banco.get_pending_transactions(1, CERTIFY_LOCK);

  for (const auto& transaction : x) {
      std::cout << transaction << std::endl;
  }

  //banco.print_lock_info();

  std::cout << "mensagem\n";

  //tabela.print_lock_info();

  

}

