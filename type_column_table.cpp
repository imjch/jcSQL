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
