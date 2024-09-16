#include "database/include/database.hpp"
#include "database/include/uids.hpp"
#include "database/include/transaction.hpp"


// Definition of object constructors 

Database::Database(char obj_name) : Object{obj_name}, tablespaces_{} {} 

Tablespace::Tablespace(char obj_name, Database* database) : Object{obj_name}, database_{database}, pages_{} {} 

Page::Page(char obj_name, Tablespace* tablespace) : Object{obj_name}, tablespace_{tablespace}, tuples_{} {} 

Tuple::Tuple(char obj_name, Page* page) : Object{obj_name}, page_{page} {} 



// Lock functions for each object.

void Database::block_from_below(Transaction& transaction, LockType lock_type) {

  // Só vai entrar aqui se o bloqueio puder ser concedido. A verificação será aqui? Provavelmente fica melhor dentro do próprio escalonador.

  object_lock_info_[lock_type] = true;

  bool* lock_info_ptr = const_cast<bool*>(&object_lock_info_[lock_type]);

  BlockInformation block_info{lock_info_ptr, lock_type};

  transaction.push_block_info(block_info);

}


