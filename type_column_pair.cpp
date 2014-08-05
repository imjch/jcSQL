#include "type_column_pair.h"


type_column_pair::type_column_pair(val_type v, const std::string& col)
:type(v), column_name(col)
{
}

type_column_pair::~type_column_pair()
{
}

void type_column_pair::set_type(val_type  v)
{
    type = v;
}
void type_column_pair::set_column(const std::string& col_name)
{
    column_name = col_name;
}

val_type type_column_pair::get_type()
{
    return type;
}

std::string type_column_pair::get_column()
{
    return column_name;
}
