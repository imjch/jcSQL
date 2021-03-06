#pragma once
#include <string>
#include "column_attr.h"


class column_attr_pair
{
public:
    typedef std::string column_name;
    typedef std::string column_val;
    column_attr_pair(column_attr,const std::string&);
    column_attr_pair();
    ~column_attr_pair();
    void set_column_name(const column_name&);
    void set_attr(column_attr attr);
    const column_name& get_column_name() const;
    const column_attr get_attr()const;
private:
    column_attr attr;
    column_name col_name;
};
bool operator<(const column_attr_pair&, const column_attr_pair&);

