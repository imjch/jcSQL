#include "select_operation.h"

select_operation::select_operation()
{
    
}

select_operation::select_operation(const std::string& t_n, column_list& l, logic_conn_table& t)
:cols(l), l_table(t)
{
    operation::set_table_name(t_n);
}
select_operation::~select_operation()
{
    operation::~operation();
}

void select_operation::set_cols(column_list& li)
{
    cols = li;
}

void select_operation::add_col(const std::string& c)
{
    cols.push_back(c);
}

void select_operation::set_logic_table(logic_conn_table& t)
{
    l_table = t;
}

