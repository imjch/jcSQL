#pragma once
#include "operation.h"
#include "type_column_table.h"
class create_operation:public operation
{
public:
    create_operation();
    create_operation(const std::string&, type_column_table&);
    ~create_operation();
    void set_type_column_table(type_column_table&);
   // result_list execute();

private:
    type_column_table table;
};

