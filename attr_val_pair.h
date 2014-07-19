#pragma once
#include <string>
#include "val_type.h"
#include "result_list.h"
class attr_val_pair
{
public:
    attr_val_pair(const std::string&, result_list&, val_type);
    attr_val_pair();
    ~attr_val_pair();
    void set_attr(const std::string&);
    void set_val_type(val_type);
    void add_val(const std::string&);
    void set_result_list(const result_list&);
private:
    std::string attr_name;
    val_type v_t;
    result_list result;
};

