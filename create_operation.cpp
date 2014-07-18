#include "create_operation.h"


create_operation::create_operation()
{
}

create_operation::~create_operation()
{
    operation::~operation();
}

void create_operation::set_type_column_table(type_column_table& t)
{
    table = t;
}
