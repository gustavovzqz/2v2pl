#include "database/include/database.hpp"
#include "database/include/lock_types.hpp"
#include "database/include/transaction.hpp"
#include <stdexcept>


// Definition of object constructors 

Database::Database(char obj_name) : Object{obj_name}, tablespaces_{} {} 

Tablespace::Tablespace(char obj_name, Database* database) : Object{obj_name}, database_{database}, pages_{} {} 

Page::Page(char obj_name, Tablespace* tablespace) : Object{obj_name}, tablespace_{tablespace}, tuples_{} {} 

Tuple::Tuple(char obj_name, Page* page) : Object{obj_name}, page_{page} {} 



// Block from below --

void Database::block_from_below(Transaction& transaction, LockType lock_request) {


  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());

}


void Tablespace::block_from_below(Transaction& transaction, LockType lock_request) {

  
  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());

  
  database_->block_from_below(transaction, lock_request); 
  
}



void Page::block_from_below(Transaction& transaction, LockType lock_request) {

  
  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());

  
  tablespace_->block_from_below(transaction, lock_request); 
  
}


void Tuple::block_from_below(Transaction& , LockType ) {
  

  throw std::runtime_error("Isso não era para ser possível!");
  return;
  
}


// Block from above!

void Database::block_from_above(Transaction& , LockType ) {

  throw std::runtime_error("Isso não era para ser possível!");
  return;

}


void Tablespace::block_from_above(Transaction& transaction, LockType lock_request) {


  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());


  for (auto &page : pages_) {
    page->block_from_above(transaction, lock_request);
  }

}


void Page::block_from_above(Transaction& transaction, LockType lock_request) {


  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());


  for (auto &tuple: tuples_) {
    tuple->block_from_above(transaction, lock_request);
  }

}


void Tuple::block_from_above(Transaction& transaction, LockType lock_request) {


  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());

}


// Now, the block functions.

void Database::block(Transaction& transaction, LockType lock_request) {

  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());

  for (auto &tablespace: tablespaces_) {
    tablespace->block_from_above(transaction, lock_request);
  }

// block_from_below() ... nothing above database 

}

void Tablespace::block(Transaction& transaction, LockType lock_request) {

  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());

  LockType intentional_lock = get_intentional_from_lock(lock_request);

  database_->block_from_below(transaction, intentional_lock);

  for (auto &page : pages_){
    page->block_from_above(transaction, lock_request);
  }

}


void Page::block(Transaction& transaction, LockType lock_request) {

  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());

  LockType intentional_lock = get_intentional_from_lock(lock_request);

  tablespace_->block_from_below(transaction, intentional_lock);

  for (auto &tuple: tuples_){
    tuple->block_from_above(transaction, lock_request);
  }

}

void Tuple::block(Transaction& transaction, LockType lock_request) {

  transaction.push_object_info(this);

  object_lock_info_[lock_request].insert(transaction.get_id());

  LockType intentional_lock = get_intentional_from_lock(lock_request);

  page_->block_from_below(transaction, intentional_lock);

  // nothing below tuple

}

// "Add" functions

void Database::add_tablespace(Tablespace* tablespace) {
    if (tablespace) {
        tablespaces_.push_back(tablespace);
    }
}

void Tablespace::add_page(Page* page) {
    if (page) {
        pages_.push_back(page);
    }
}

void Page::add_tuple(Tuple* tuple) {
    if (tuple) {
        tuples_.push_back(tuple);
    }
}





