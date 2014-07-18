#include "select_operation.h"

select_operation::select_operation()
{
    
}
select_operation::~select_operation()
{
    operation::~operation();
}

void select_operation::add_cols(result_list& c)
{
    add_cols(c.begin(),c.end());
}

void select_operation::add_logic_table(logic_conn_table& t)
{
    l_table = t;
}

