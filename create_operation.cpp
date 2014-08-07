#include "create_operation.h"
#include <string>
#include "table_attr.h"

create_operation::create_operation(const std::string& t_name, type_column_list& t)
:create_operation(t_name,t,table_attr())
{
    
}

create_operation::create_operation(const std::string& t_name, type_column_list& t, table_attr& t_a)
: t_c_table(t), t_attr(t_a)
{
    operation::set_table_name(t_name);
}

void create_operation::set_table_attr(table_attr& t_a)
{
    t_attr = t_a;
}

table_attr create_operation::get_table_attr()
{
    return t_attr;
}

create_operation::~create_operation()
{
    operation::~operation();
}

void create_operation::set_type_column_list(type_column_list& t)
{
    t_c_table = t;
}

type_column_list create_operation::get_type_column_list()
{
    return t_c_table;
}