#include "column_attr_list.h"


column_attr_list::column_attr_list()
{
}


column_attr_list::~column_attr_list()
{
}

void column_attr_list::add_column_pair(column_attr_pair& pair)
{
    alter_column_pair(pair);
}

void column_attr_list::alter_column_pair(column_attr_pair& pair)
{
    items.erase(pair);
    items.insert(pair);
}

column_attr_list::iterator column_attr_list::begin()
{
    return items.begin();
}

column_attr_list::iterator column_attr_list::end()
{
    return items.end();
}

size_t column_attr_list::size()
{
    return items.size();
}

bool column_attr_list::empty()
{
    return items.empty();
}

