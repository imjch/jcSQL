#pragma once
#include "operation.h"
#include "operators.h"
#include <utility>
#include <string>
#include "type_column_table.h"
class alter_operation :
    public operation
{
public:
    alter_operation();
    alter_operation(operators, type_column_table);
    ~alter_operation();
    void set_op(operators op);
    void add_typ_column(type_column_pair& pair);
private:
    std::pair<operators,type_column_table> columns_list;
};

