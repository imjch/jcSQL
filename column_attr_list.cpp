#include "column_attr_list.h"


column_attr_list::column_attr_list()
{
}


column_attr_list::~column_attr_list()
{
}

void column_attr_list::add_column_pair(column_attr_pair& pair)
{
    c_a_list.push_back(pair);
}

column_attr_list::iterator column_attr_list::begin()
{
    return c_a_list.begin();
}

column_attr_list::iterator column_attr_list::end()
{
    return c_a_list.end();
}

size_t column_attr_list::size()
{
    return c_a_list.size();
}