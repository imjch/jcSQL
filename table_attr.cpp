#include "table_attr.h"

table_attr::a_c_table table_attr::table;

table_attr::table_attr()
{
}

table_attr::~table_attr()
{
}

void table_attr::add_column_attr(column_attr_pair& pair)
{
    add_column_attr(pair.get_column_name(),pair.get_attr());
}

void table_attr::add_column_attr(const std::string& col, column_attr attr)
{
    table[attr].push_back(col);
}
table_attr::column_list table_attr::get_column_list(column_attr attr)
{
    if (table.count(attr)>0)
    {
        return table[attr];
    }
}

table_attr::iterator table_attr::begin()
{
    return table.begin();
}

table_attr::iterator table_attr::end()
{
    return table.end();
}




