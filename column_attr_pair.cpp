#include "column_attr_pair.h"


column_attr_pair::column_attr_pair(const std::string& col,column_attr val)
:column_name(col), attr(val)
{
}

column_attr_pair::~column_attr_pair()
{
}

void column_attr_pair::set_column_name(const std::string& col)
{
    column_name = col;
}

void column_attr_pair::set_attr(column_attr val)
{
    attr = val;
}

std::string column_attr_pair::get_column_name()
{
    return column_name;
}

column_attr column_attr_pair::get_attr()
{
    return attr;
}