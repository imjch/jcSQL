#pragma once
#include <string>
#include <list>
#include "logic_conn_table.h"
#include "operation.h"
class select_operation:public operation
{
public:
    select_operation();
    ~select_operation();

    template <typename input_iterator>
    void add_cols(input_iterator begin, input_iterator end);
    void add_cols(result_list&);
    void add_logic_table(logic_conn_table&);
private:
    std::list<std::string> cols;
    logic_conn_table l_table;
};

template <typename input_iterator>
void select_operation::add_cols(input_iterator begin, input_iterator end)
{
    while (begin!=end)
    {
        cols.push_back(*begin);
        ++begin;
    }
}
