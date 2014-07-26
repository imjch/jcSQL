#include "create_operation.h"
#include <string>

create_operation::create_operation()
{
}

create_operation::create_operation(const std::string& t_name, type_column_table& t):
table(t)
{
    operation::set_table_name(t_name);   
}

create_operation::~create_operation()
{
    operation::~operation();
}

void create_operation::set_type_column_table(type_column_table& t)
{
    table = t;
}
//result_list create_operation::execute()
//{
//    return result_list("sss");
//}
//
