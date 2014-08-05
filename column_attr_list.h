#pragma once
#include <list>
#include "column_attr_pair.h"
class column_attr_list
{
public:
    typedef std::list<column_attr_pair>::iterator iterator;
    column_attr_list();
    ~column_attr_list();
    void add_column_pair(column_attr_pair&);
    iterator begin();
    iterator end();
    size_t size();
private:
    std::list<column_attr_pair> c_a_list;
};

