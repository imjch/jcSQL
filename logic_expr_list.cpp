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