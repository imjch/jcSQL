#pragma once
#include <list>
#include "logic_expr.h"
class logic_expr_list
{
public:
    typedef std::list<logic_expr>::iterator iterator;
    logic_expr_list();
    ~logic_expr_list();
    void add_logic_expr(logic_expr&);
    iterator begin();
    iterator end();
    size_t size();
private:
    std::list<logic_expr> items;
};

