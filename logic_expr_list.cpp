#include "logic_expr_list.h"


logic_expr_list::logic_expr_list()
{
}

logic_expr_list::~logic_expr_list()
{
}

void logic_expr_list::add_logic_expr(logic_expr& expr)
{
    if (logic_exprs.count(expr.get_attr()))
    {
        logic_exprs[expr.get_attr()].insert(std::make_pair(expr.get_op(),expr));
    }
    else
    {
        std::map<logic_op_type, logic_expr> m;
        m.insert(std::make_pair(expr.get_op(),expr));
        logic_exprs.insert(std::make_pair(expr.get_attr(),m));
    }
}

bool logic_expr_list::contain(const std::string& column_name)
{
    return logic_exprs.count(column_name) > 0 ? true : false;
}

logic_expr_list::iterator logic_expr_list::begin()
{
    return logic_exprs.begin();
}

logic_expr_list::iterator logic_expr_list::end()
{
    return logic_exprs.end();
}

size_t logic_expr_list::size()
{
    return logic_exprs.size();
}

bool logic_expr_list::empty()
{
    return logic_exprs.empty();
}