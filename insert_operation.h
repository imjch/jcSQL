#pragma once
#include "operation.h"
#include <list>
#include "attr_val_table.h"
class insert_operation:public operation
{
public:
    insert_operation(const std::string&,attr_val_table&);
    insert_operation();
    ~insert_operation();
    void set_attr_val_table(attr_val_table&);
    void add_attr_val_pair(attr_val_pair&);
    attr_val_table get_attr_val_table();
    //result_list insert_operation::execute();
private:
    attr_val_table list;
};

