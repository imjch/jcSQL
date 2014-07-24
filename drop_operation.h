#pragma once
#include "operation.h"
#include <string>
class drop_operation:public operation
{
public:
    drop_operation();
    drop_operation(const std::string&);
    ~drop_operation();
    result_list drop_operation::execute();
};

