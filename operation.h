#pragma once
#include <string>
#include "result_list.h"
class operation
{
public:
    operation();
    virtual ~operation()=0;
    virtual result_list execute() = 0;
    void set_table_name(const std::string&);
    
private:
    std::string table_name;
};

