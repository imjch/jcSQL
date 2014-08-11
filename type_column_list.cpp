#include "type_column_list.h"
#include "val_type.h"
type_column_list::type_column_list()
{
}

type_column_list::~type_column_list()
{
}

void type_column_list::add_type_column(const type_column_pair& pair)
{
    alter_column_type(pair);
}

void type_column_list::add_type_column(iterator& begin, iterator& end)
{
    while (begin != end)
    {
        add_type_column(begin->second);
        ++begin;
    }
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

void type_column_list::remove_type_column(const type_column_pair& pair)
{
    items.erase(pair.get_column());
}

void type_column_list::remove_type_column(iterator& begin,iterator& end)
{
    while (begin!=end)
    {
        remove_type_column(begin->second);
        ++begin;
    }
}

void type_column_list::alter_column_type(iterator& begin, iterator& end)
{
    while (begin!=end)
    {
        alter_column_type(begin->second);
        ++begin;
    }
}

void type_column_list::alter_column_type(const type_column_pair& pair)
{
    items.erase(pair.get_column());
    items.insert(std::make_pair(pair.get_column(), pair));
}

type_column_pair type_column_list::get_type_column_pair(const std::string& col)
{
    return items[col];
}

bool type_column_list::contain(const std::string& col_name)
{
    return items.count(col_name) > 0 ? true : false;
}