#pragma once
#include <string>
class operation
{
public:
    operation();
    virtual ~operation()=0;
    void set_table_name(const std::string&);
private:
    std::string table_name;
};

