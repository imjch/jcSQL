#include "type_column_list.h"
#include "column_attr.h"
type_column_list::type_column_list()
{
}

type_column_list::~type_column_list()
{
}

void type_column_list::add_type_column(type_column_pair& pair)
{
    items.insert(pair);
}

void type_column_list::add_type_column(iterator& begin, iterator& end)
{
    items.insert(begin,end);
}

void type_column_list::alter_column(type_column_pair& pair)
{
    items.find(pair)->set_type(PRIMARY_KEY);
}

size_t type_column_list::size()
{
    return items.size();
}

type_column_list::iterator type_column_list::begin()
{
    return items.begin();
}

type_column_list::iterator type_column_list::end()
{
    return items.end();
}

bool type_column_list::empty()
{
    return items.empty();
}

void type_column_list::remove_type_column(type_column_pair& pair)
{
    items.erase(pair);
}

void type_column_list::remove_type_column(iterator& begin,iterator& end)
{
    items.erase(begin,end);
}