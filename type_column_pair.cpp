#include "type_column_pair.h"


type_column_pair::type_column_pair(const std::string& v, const std::string& col)
:type(v), column_name(col)
{
}


type_column_pair::~type_column_pair()
{
}

void type_column_pair::set_type(const std::string&  v)
{
    type = v;
}
void type_column_pair::set_column(const std::string& col_name)
{
    column_name = col_name;
}
