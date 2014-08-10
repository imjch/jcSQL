#include "type_column_list.h"
#include "val_type.h"
type_column_list::type_column_list()
{
}

type_column_list::~type_column_list()
{
}

void type_column_list::add_type_column(type_column_pair& pair)
{
    alter_column_type(pair);
}

void type_column_list::add_type_column(iterator& begin, iterator& end)
{
    alter_column_type(begin, end);
}

void type_column_list::alter_column_type(type_column_pair& pair)
{
    items.erase(pair);
    items.insert(pair);
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
    while (begin!=end)
    {
        items.erase(*begin);
        ++begin;
    }
}

void type_column_list::alter_column_type(iterator& begin, iterator& end)
{
    add_type_column(begin, end);
}