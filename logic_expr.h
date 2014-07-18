#pragma once
#include <string>
#include "result_list.h"
#include "val_type.h"
class logic_expr
{
public:
    logic_expr(const std::string&, const std::string& ,result_list&,val_type);
    //logic_expr();
    ~logic_expr();
    void set_attr(const std::string&);
    void set_op(const std::string&);
    void add_val(const std::string&);
private:
    std::string attr_name;
    std::string op;
    val_type val_t;
    result_list result;
};

