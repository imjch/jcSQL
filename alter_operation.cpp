#include "alter_operation.h"
#include "type_column_pair.h"

alter_operation::alter_operation()
{
}

alter_operation::alter_operation(operators op, type_column_table list)
:columns_list(op,list)
{
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