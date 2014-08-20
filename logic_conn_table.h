#pragma once
#include "logic_conn_table.h"
#include "logic_expr_list.h"
#include <unordered_map>
#include <string>
#include <utility>
#include "logic_conn_type.h"
class logic_conn_table
{
public:
    typedef std::unordered_map<logic_conn_type, logic_expr_list>::iterator iterator;
    logic_conn_table();
    ~logic_conn_table();
    logic_expr_list get_logic_expr_list(logic_conn_type);
    void add_logic_expr_list(logic_conn_type, logic_expr_list&);
    iterator begin();
    iterator end();
    size_t size();
    bool empty();
    bool contain(logic_conn_type);
private:
    std::unordered_map<logic_conn_type,logic_expr_list> table;
};

