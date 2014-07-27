#pragma once
#include <string>
#include "result_list.h"
#include "val_type.h"
#include "attr_val_pair.h"
class logic_expr
{
public:
    logic_expr(const std::string&, const std::string&, result_list&, val_type);
    logic_expr();
    ~logic_expr();
    void set_attr(const std::string&);
    void set_op(const std::string&);
    void add_val(const std::string&);
    void set_val_type(val_type v);
private:
    attr_val_pair avp;
    std::string op;
};

