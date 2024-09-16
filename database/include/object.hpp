#ifndef DATABASE_INCLUDE_OBJECT_HPP
#define DATABASE_INCLUDE_OBJECT_HPP

#include "transaction.hpp"
#include "uids.hpp"

#include <array>

class Object {


  char object_name_;

  protected: 

  std::array<bool, 8> object_lock_info_; 

  virtual void block_from_below(Transaction& transaction, LockType lock_type) = 0;
  virtual void block_from_above(Transaction& transaction, LockType lock_type) = 0;
  
  public:
  virtual void block(Transaction& transaction, LockType lock_type) = 0;
  bool is_open_to_block(LockType lock_type); 

  Object(char obj_name);

  char get_object_name();  

};

#endif
