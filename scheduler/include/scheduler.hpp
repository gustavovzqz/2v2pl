#ifndef SCHEDULER_INCLUDE_SCHEDULER_HPP
#define SCHEDULER_INCLUDE_SCHEDULER_HPP

#include <list>
#include <map>

#include "database/include/database.hpp"
#include "database/include/object.hpp"
#include "database/include/operation.hpp"
#include "database/include/transaction.hpp"

class Scheduler {
  std::list<Operation> operations_;
  std::vector<Transaction*> transactions_;
  std::map<char, Object*> object_map_;

 public:
  Scheduler(std::list<Operation> operations,
            std::vector<Transaction*> transactions,
            std::map<char, Object*> name_to_object_map);
  std::list<Operation> get_2v2pl_schedule();
};

#endif