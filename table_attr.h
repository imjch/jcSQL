#pragma once
#include "column_attr_pair.h"
#include "column_attr.h"
#include <unordered_map>
#include <string>
#include <list>
class table_attr
{
private:
    typedef std::unordered_map<column_attr, std::list<std::string>> a_c_table;
    table_attr();
    ~table_attr();
    static a_c_table  table;

public:
    typedef a_c_table::iterator iterator;
    typedef std::list<std::string> column_list;
    static void add_column_attr(column_attr_pair&);
    static void table_attr::add_column_attr(const std::string&,column_attr);
   
    static column_list get_column_list(column_attr);
    static iterator begin();
    static iterator end();
};

