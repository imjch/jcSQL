#pragma once
#include <set>
#include "column_attr_pair.h"
class column_attr_list
{
public:
    typedef std::set<column_attr_pair>::iterator iterator;
    column_attr_list();
    ~column_attr_list();
    void add_column_pair(column_attr_pair&);
    iterator begin();
    iterator end();
    size_t size();
    bool empty();
private:
    std::set<column_attr_pair> items;
};

