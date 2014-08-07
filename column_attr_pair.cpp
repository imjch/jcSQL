#include "column_attr_pair.h"


column_attr_pair::column_attr_pair(column_attr val, const std::string& col)
:column_name(col), attr(val)
{
}
column_attr_pair::column_attr_pair()
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

const std::string& column_attr_pair::get_column_name() const
{
    return column_name;
}

const column_attr column_attr_pair::get_attr() const
{
    return attr;
}

bool operator<(const column_attr_pair& x, const column_attr_pair& y)
{
    return x.get_column_name() < y.get_column_name();
}
