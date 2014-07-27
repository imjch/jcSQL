#pragma once
#include "logic_conn_table.h"
#include "logic_expr_list.h"
#include <unordered_map>
#include <string>
#include <utility>
class logic_conn_table
{
public:
    logic_conn_table();
    ~logic_conn_table();
    void add_logic_conn_list(std::pair<std::string,logic_expr_list>&);
private:
    std::unordered_map<std::string,logic_expr_list> table;
};

