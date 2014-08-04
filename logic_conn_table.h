#pragma once
#include "logic_conn_table.h"
#include "logic_expr_list.h"
#include <unordered_map>
#include <string>
#include <utility>
class logic_conn_table
{
public:
    typedef std::unordered_map<std::string, logic_expr_list>::iterator iterator;
    logic_conn_table();
    ~logic_conn_table();
    logic_expr_list get_logic_expr_list(const std::string&);
    void add_logic_conn_list(std::pair<std::string,logic_expr_list>&);
    iterator begin();
    iterator end();
    size_t size();
private:
    std::unordered_map<std::string,logic_expr_list> table;
};

