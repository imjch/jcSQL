#pragma once
#include <string>

class type_column_pair
{
public:
    type_column_pair(const std::string&, const std::string&);
    ~type_column_pair();
    void set_type(const std::string&);
    void set_column(const std::string&);
    std::string get_type();
    std::string get_column();
private:
    std::string type;
    std::string column_name;
};

