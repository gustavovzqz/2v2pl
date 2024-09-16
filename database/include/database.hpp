#ifndef DATABASE_INCLUDE_DATABASE_HPP
#define DATABASE_INCLUDE_DATABASE_HPP

#include <vector>
#include <memory>
#include "database/include/uids.hpp"
#include "object.hpp"


class Tablespace;
class Page;
class Tuple;


class Database : public Object { 
  Database(char obj_name); 


  std::vector<std::unique_ptr<Tablespace>> tablespaces_;

  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;

public: 

  void block(Transaction& transaction, LockType lock_type) override;

};


class Tablespace : public Object { 
  Tablespace(char obj_name, Database* database); 

  Database* database_;


  std::vector<std::unique_ptr<Page>> pages_;

  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;

public:


  void block(Transaction& transaction, LockType lock_type) override;
};


class Page : public Object { 
  Page(char obj_name, Tablespace* tablespace); 

  Tablespace* tablespace_;


  std::vector<std::unique_ptr<Tuple>> tuples_;

  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;

public:

  void block(Transaction& transaction, LockType lock_type) override;
};


class Tuple : public Object{ 
  Tuple(char obj_name, Page* page); 

  Page * page_;

  void block_from_below(Transaction& transaction, LockType lock_type) override;
  void block_from_above(Transaction& transaction, LockType lock_type) override;

public:

  void block(Transaction& transaction, LockType lock_type) override;

};




#endif

