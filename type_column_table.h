#pragma once
#include "type_column_pair.h"
#include <list>
class type_column_table
{
public:
    type_column_table();
    ~type_column_table();
    void add_type_column(type_column_pair& pair);
private:
    std::list<type_column_pair> table;
};

