#include "type_column_table.h"


type_column_table::type_column_table()
{
}

type_column_table::~type_column_table()
{
}

void type_column_table::add_type_column(type_column_pair& pair)
{
    table.push_back(pair);
}

size_t type_column_table::size()
{
    return table.size();
}

type_column_table::iterator type_column_table::begin()
{
    return table.begin();
}

type_column_table::iterator type_column_table::end()
{
    return table.end();
}
