#pragma once
#include <string>
#include "result_list.h"

class operation
{
public:
    operation();
    virtual ~operation()=0;
    void set_table_name(const std::string&);
    const std::string& get_table_name() const;
private:
    std::string table_name;
};

