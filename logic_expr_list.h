#pragma once
#include <list>
#include "logic_expr.h"
class logic_expr_list
{
public:
    logic_expr_list();
    ~logic_expr_list();
    void add_logic_expr(logic_expr&);
private:
    std::list<logic_expr> items;
};

