#ifndef DATABASE_INCLUDE_DATABASE_HPP
#define DATABASE_INCLUDE_DATABASE_HPP

#include <vector>
#include "object.hpp"


class Tablespace;
class Page;
class Tuple;


class Database : public Object { 
  Database(char obj_name); 

  char object_name;
  std::vector<Tablespace> tablespaces_;

};


class Tablespace : public Object { 
  Tablespace(Database* database); 

  char object_name;

  std::vector<Page> pages_;

};


class Page : public Object { 
  Page(Tablespace* tablespace); 

  char object_name;

  std::vector<Tuple> tuples_;

};


class Tuple : public Object{ 
  Tuple(Page* page); 

  char object_name;

};




#endif

