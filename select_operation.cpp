#include "select_operation.h"


select_operation::select_operation(const std::string& s, std::list<std::string>& l, logic_conn_table& t):
                    table_name(s),
                    cols(l),
                    l_table(t)
{
}
select_operation::select_operation()
{
}
select_operation::~select_operation()
{
}

void select_operation::add_table_name(const std::string& t_name)
{
    table_name = t_name;
}

void select_operation::add_cols(result_list& c)
{
    add_cols(c.begin(),c.end());
}

void select_operation::add_table(logic_conn_table& t)
{
    l_table = t;
}

