#pragma once
#include "type_column_pair.h"
#include <list>
class type_column_table
{
public:
    typedef  std::list<type_column_pair>::iterator iterator;
    type_column_table();
    ~type_column_table();
    void add_type_column(type_column_pair& pair);
    size_t size();
    iterator begin();
    iterator end();
private:
    std::list<type_column_pair> table;
};

