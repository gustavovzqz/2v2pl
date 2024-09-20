#ifndef DATABASE_INCLUDE_DATABASE_HPP
#define DATABASE_INCLUDE_DATABASE_HPP

#include <vector>
#include <memory>
#include "lock_types.hpp"
#include "object.hpp"


class Tablespace;
class Page;
class Tuple;


class Database : public Object { 

  std::vector<std::unique_ptr<Tablespace>> tablespaces_;

public:

  Database(char obj_name); 
  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;
  void block(Transaction& transaction, LockType lock_type) override;

};


class Tablespace : public Object { 

  Database* database_;
  std::vector<std::unique_ptr<Page>> pages_;

public:

  Tablespace(char obj_name, Database* database); 
  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;
  void block(Transaction& transaction, LockType lock_type) override;
};


class Page : public Object { 

  Tablespace* tablespace_;
  std::vector<std::unique_ptr<Tuple>> tuples_;

public:

  Page(char obj_name, Tablespace* tablespace); 
  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;
  void block(Transaction& transaction, LockType lock_type) override;

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

