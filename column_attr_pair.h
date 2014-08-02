#pragma once
#include <string>
#include "column_attr.h"
class column_attr_pair
{
public:
    column_attr_pair(column_attr,const std::string&);
    column_attr_pair();
    ~column_attr_pair();
    void set_column_name(const std::string&);
    void set_attr(column_attr attr);
    std::string get_column_name();
    column_attr get_attr();
private:
    column_attr attr;
    std::string column_name;
};

