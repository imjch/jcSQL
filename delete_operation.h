#pragma once
#include "operation.h"
#include "logic_conn_table.h"
class delete_operation :
    public operation
{
public:
    delete_operation();
    delete_operation(const std::string&, logic_conn_table&);
    ~delete_operation();
    void set_table_name(const std::string&);
    //result_list execute();
private:
    logic_conn_table table;
};

