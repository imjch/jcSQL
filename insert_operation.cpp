#include "insert_operation.h"


insert_operation::insert_operation(const std::string& t_name,attr_val_list &l)
:list(l)
{
    operation::set_table_name(t_name);
}

insert_operation::insert_operation()
{
}

insert_operation::~insert_operation()
{
    operation::~operation();
}

void insert_operation::set_attr_val_list(attr_val_list& li)
{
    list = li;
}

void insert_operation::add_attr_val_pair(attr_val_pair& pair)
{
    list.add_attr_val(pair);
}

attr_val_list insert_operation::get_attr_val_list()
{
    return list;
}