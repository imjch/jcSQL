#include "alter_operation.h"
#include "type_column_pair.h"

alter_operation::alter_operation()
{
}

alter_operation::alter_operation(const std::string& name,operators op, type_column_list list)
:columns_list(op,list)
{
    operation::set_table_name(name);
}

alter_operation::~alter_operation()
{
}

void alter_operation::set_op(operators op)
{
    columns_list.first = op;
}

void alter_operation::add_typ_column(type_column_pair& pair)
{
    columns_list.second.add_type_column(pair);
}

operators alter_operation::get_operators()
{
    return columns_list.first;
}

type_column_list alter_operation::get_type_column_list()
{
    return columns_list.second;
}

