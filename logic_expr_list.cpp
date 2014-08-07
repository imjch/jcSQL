#include "logic_expr_list.h"


logic_expr_list::logic_expr_list()
{
}

logic_expr_list::~logic_expr_list()
{
}

void logic_expr_list::add_logic_expr(logic_expr& expr)
{
    items.push_back(expr);
}

logic_expr_list::iterator logic_expr_list::begin()
{
    return items.begin();
}

logic_expr_list::iterator logic_expr_list::end()
{
    return items.end();
}

size_t logic_expr_list::size()
{
    return items.size();
}

bool logic_expr_list::empty()
{
    return items.empty();
}