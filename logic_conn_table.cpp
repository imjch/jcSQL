#include "logic_conn_table.h"
#include <assert.h>

logic_conn_table::logic_conn_table()
{
}

logic_conn_table::~logic_conn_table()
{
}

void logic_conn_table::add_logic_conn_list(std::pair<std::string,logic_expr_list>& pair)
{
    table.insert(pair);
}

logic_conn_table::iterator logic_conn_table::begin()
{
    return table.begin();
}

logic_conn_table::iterator logic_conn_table::end()
{
    return table.end();
}

size_t logic_conn_table::size()
{
    return table.size();
}

logic_expr_list logic_conn_table::get_logic_expr_list(const std::string& l_op)
{
    assert(l_op.size()>0);
    return table[l_op];
}