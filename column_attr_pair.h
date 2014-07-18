#pragma once
#include <string>
#include "column_attr.h"
class column_attr_pair
{
public:
    column_attr_pair(const std::string&,column_attr);
    ~column_attr_pair();

    void set_column_name(const std::string&);
    void set_attr(column_attr attr);
    std::string get_column_name();
    column_attr get_attr();
private:
    std::string column_name;
    column_attr attr;
};

