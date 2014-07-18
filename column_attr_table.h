#pragma once
#include "column_attr_pair.h"
#include "column_attr.h"
#include <unordered_map>
#include <string>
#include <list>
class column_attr_table
{
public:
    typedef std::unordered_map<std::string, std::list<column_attr>> c_a_table;
    static void add_column_attr(column_attr_pair&);
    ~column_attr_table();
private:
    column_attr_table();
    static c_a_table  table;
};

