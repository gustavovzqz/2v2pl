#ifndef DATABASE_INCLUDE_DATABASE_HPP
#define DATABASE_INCLUDE_DATABASE_HPP

#include <vector>
#include "lock_types.hpp"
#include "object.hpp"


class Tablespace;
class Page;
class Tuple;


class Database : public Object { 

  std::vector<Tablespace*> tablespaces_;

public:

  Database(char obj_name); 
  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;
  void block(Transaction& transaction, LockType lock_type) override;
  void add_tablespace(Tablespace* tablespace);

};


class Tablespace : public Object { 

  Database* database_;
  std::vector<Page*> pages_;

public:

  Tablespace(char obj_name, Database* database); 
  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;
  void block(Transaction& transaction, LockType lock_type) override;
  void add_page(Page* page);

};


class Page : public Object { 

  Tablespace* tablespace_;
  std::vector<Tuple*> tuples_;

public:

  Page(char obj_name, Tablespace* tablespace); 
  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;
  void block(Transaction& transaction, LockType lock_type) override;
  void add_tuple(Tuple* tuple);


};


class Tuple : public Object{ 

  Page * page_;

public:

  Tuple(char obj_name, Page* page); 
  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;
  void block(Transaction& transaction, LockType lock_type) override;

};




#endif

