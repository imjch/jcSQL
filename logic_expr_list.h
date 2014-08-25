#pragma once
#include <map>
#include <list>
#include <string>
#include "logic_expr.h"
#include <map>
#include "operators.h"
class logic_expr_list
{
public:
    typedef std::string column_name;
    typedef std::map<column_name, std::map<logic_op_type, logic_expr>> logic_expr_container;
    typedef logic_expr_container::iterator iterator;
    logic_expr_list();
    ~logic_expr_list();
    void add_logic_expr(logic_expr&);
    iterator begin();
    iterator end();
    size_t size();
    bool contain(const column_name&);
    bool empty();
private:
    logic_expr_container logic_exprs;
};

