#pragma once
#include "operation.h"
#include <list>
#include "attr_val_list.h"
class insert_operation:public operation
{
public:
    insert_operation(const std::string&,attr_val_list&);
    insert_operation();
    ~insert_operation();
    void set_attr_val_list(attr_val_list&);
    result_list insert_operation::execute();
private:
    attr_val_list list;
};

