#ifndef DATABASE_INCLUDE_TRANSACTION_HPP
#define DATABASE_INCLUDE_TRANSACTION_HPP

#include "uids.hpp"
#include <vector>

struct BlockInformation {

  bool * block_value; 
  LockType lock_type;

  public:
  BlockInformation(bool* block_value, LockType lock_type);

};


class Transaction {

  std::vector<BlockInformation> block_info_;


  public:
  
  void abort_transaction(); 
  void upgrade_write_to_certify();
  void push_block_info(BlockInformation block_info);

};





#endif
