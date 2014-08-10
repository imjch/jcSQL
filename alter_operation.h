#pragma once
#include "operation.h"
#include "operators.h"
#include <utility>
#include <string>
#include "type_column_list.h"
class alter_operation :
    public operation
{
public:
    alter_operation();
    alter_operation(const std::string&,operators, type_column_list);
    ~alter_operation();
    void set_op(operators op);
    void add_typ_column(type_column_pair& pair);
    type_column_list get_type_column_list();
    operators get_operators();
private:
    std::pair<operators,type_column_list> columns_list;
};

