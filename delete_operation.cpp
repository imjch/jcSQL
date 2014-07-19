#include "delete_operation.h"


delete_operation::delete_operation()
{
}

delete_operation::delete_operation(const std::string& t_name, logic_conn_table t)
:table(t)
{
    operation::set_table_name(t_name);
}


delete_operation::~delete_operation()
{
    operation::~operation();
}
