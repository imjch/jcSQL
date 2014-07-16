#include "logic_conn_table.h"


logic_conn_table::logic_conn_table()
{
}

logic_conn_table::~logic_conn_table()
{
}

void logic_conn_table::add_logic_conn_list(std::pair<std::string, logic_expr_list>& pair)
{
    table.insert(pair);
}