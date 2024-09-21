#ifndef DATABASE_INCLUDE_OBJECT_HPP
#define DATABASE_INCLUDE_OBJECT_HPP

#include <array>
#include <map>
#include <unordered_set>

#include "lock_types.hpp"
#include "transaction.hpp"

class Object {
  char object_name_;

 protected:
  std::array<std::unordered_set<int>, 8> object_lock_info_;

  virtual void block_from_below(Transaction* transaction,
                                LockType lock_type) = 0;
  virtual void block_from_above(Transaction* transaction,
                                LockType lock_type) = 0;

 public:
  virtual void block(Transaction* transaction, LockType lock_type) = 0;
  std::unordered_set<int> get_incompatible_transactions(int transaction_id,
                                                        LockType lock_type);
  std::unordered_set<int> upgrade_write_to_certify(int transaction_id);
  void abort_transaction(int transaction_id);
  void print_lock_info();

  Object(char obj_name);

  char get_object_name();
};

std::map<char, Object*> get_object_map(std::vector<Object*> object_vec);

#endif
