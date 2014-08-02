#pragma once
#include "operation.h"
#include "type_column_table.h"
#include "table_attr.h"

class create_operation:public operation
{
public:
    create_operation();
    create_operation(const std::string&, type_column_table&);
    create_operation(const std::string&, type_column_table&, table_attr&);
    ~create_operation();
    void set_type_column_table(type_column_table&);
    void set_table_attr(table_attr&);
    type_column_table get_type_column_table();
    table_attr& get_table_attr();
private:
    type_column_table t_c_table;
    table_attr t_attrs;
};

