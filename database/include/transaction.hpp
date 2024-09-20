#ifndef DATABASE_INCLUDE_TRANSACTION_HPP
#define DATABASE_INCLUDE_TRANSACTION_HPP

#include <vector>
#include <unordered_set>


class Object;

class Transaction {

  std::vector<Object*> objects_;

  int transaction_id_;

  public:

  Transaction(int id);
  void abort(); 
  std::unordered_set<int> upgrade_write_to_certify();
  void push_object_info(Object* block_info);
  int get_id();

};





#endif
