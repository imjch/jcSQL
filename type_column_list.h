#pragma once
#include "type_column_pair.h"
#include <set>

class type_column_list
{
public:
    typedef  std::set<type_column_pair>::iterator iterator;
    type_column_list();
    ~type_column_list();
    void add_type_column(type_column_pair&);
    void add_type_column(iterator&, iterator&);
    void remove_type_column(type_column_pair&);
    void alter_column(type_column_pair& pair);
    void type_column_list::remove_type_column(iterator& begin, iterator& end);
    size_t size();
    iterator begin();
    iterator end();
   
    bool empty();

private:
    std::set<type_column_pair> items;
};

