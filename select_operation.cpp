#include "select_operation.h"

select_operation::select_operation()
{
    
}

select_operation::select_operation(const std::string& t_n, std::list<std::string>& l, logic_conn_table& t)
:cols(l), l_table(t)
{
    operation::set_table_name(t_n);
}
select_operation::~select_operation()
{
    operation::~operation();
}

void select_operation::add_cols(result_list& c)
{
    add_cols(c.begin(),c.end());
}

void select_operation::set_logic_table(logic_conn_table& t)
{
    l_table = t;
}

