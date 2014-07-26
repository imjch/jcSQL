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

void insert_operation::set_attr_val_list(attr_val_list& l)
{
    list = l;
}

//result_list insert_operation::execute()
//{
//    return result_list("sss");
//}