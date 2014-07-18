#include "column_attr_table.h"

column_attr_table::c_a_table column_attr_table::table;
column_attr_table::column_attr_table()
{
}

column_attr_table::~column_attr_table()
{
}

void column_attr_table::add_column_attr(column_attr_pair& pair)
{
    table[pair.get_column_name()].push_back(pair.get_attr());
}
