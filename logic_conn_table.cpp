#include "logic_conn_table.h"
#include <assert.h>

logic_conn_table::logic_conn_table()
{
}

logic_conn_table::~logic_conn_table()
{
}

void logic_conn_table::add_logic_expr_list(logic_conn_type type, logic_expr_list& pair)
{
    table.insert(std::make_pair(type,pair));
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

logic_expr_list logic_conn_table::get_logic_expr_list(logic_conn_type type)
{
    return table[type];
}

bool logic_conn_table::empty()
{
    return table.empty();
}