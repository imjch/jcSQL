#include "create_operation.h"
#include <string>
#include "table_attr.h"
create_operation::create_operation()
{
}

create_operation::create_operation(const std::string& t_name, type_column_table& t)
:create_operation(t_name, t, table_attr())
{
}

create_operation::create_operation(const std::string& t_name, type_column_table& t_c_table, table_attr& t_attr)
: t_c_table(t_c_table), t_attrs(t_attr)
{
    operation::set_table_name(t_name);
}

create_operation::~create_operation()
{
    operation::~operation();
}

void create_operation::set_type_column_table(type_column_table& t)
{
    t_c_table = t;
}

void create_operation::set_table_attr(table_attr& t_attr)
{
    t_attrs = t_attr;
}

table_attr& create_operation::get_table_attr()
{
    return t_attrs;
}

type_column_table create_operation::get_type_column_table()
{
    return t_c_table;
}