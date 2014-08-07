#pragma once
#include <string>
#include "val_type.h"
class type_column_pair
{
public:
    type_column_pair(val_type, const std::string&);
    ~type_column_pair();
    void set_type(val_type);
    void set_column(const std::string&);
    val_type get_type() const;
    const std::string& get_column() const;

private:
    val_type type;
    std::string column_name;
};

bool operator<(const type_column_pair&, const type_column_pair&);
