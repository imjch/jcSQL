#include "table_attr.h"
#include <utility>

table_attr::table_attr()
{
}

table_attr::~table_attr()
{
}

void table_attr::add_column_attr(column_attr_pair& pair)
{
    table[pair.get_attr()].add_column_pair(pair);
}

column_attr_list table_attr::get_column_attr(column_attr attr)
{
    return table[attr];
}

size_t table_attr::size()
{
    return table.size();
}

table_attr::iterator table_attr::begin()
{
    return table.begin();
}

table_attr::iterator table_attr::end()
{
    return table.end();
}

bool table_attr::empty()
{
    return table.empty();
}
