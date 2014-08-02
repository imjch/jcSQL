#pragma once
#include "column_attr_pair.h"
#include "column_attr.h"
#include <unordered_map>
#include <string>
#include <list>
class table_attr
{
public:
    typedef std::list<column_attr_pair> column_attr_list;
    typedef std::unordered_map<column_attr, column_attr_list> a_c_table;
    typedef a_c_table::iterator iterator;
    table_attr();
    ~table_attr();
    void add_column_attr(column_attr_pair&);
    column_attr_list get_column_attr(column_attr);
    iterator begin();
    iterator end();
    size_t size();
private:
    a_c_table table;
};
