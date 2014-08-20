#pragma once
#include <string>
#include "result_list.h"
#include "val_type.h"
#include "logic_op_type.h"
#include "attr_val_pair.h"
class logic_expr
{
public:
    logic_expr(const std::string&, logic_op_type, result_list&, val_type);
    logic_expr();
    ~logic_expr();
    void set_attr(const std::string&);
    std::string get_attr() const;
    void set_op(logic_op_type);
    logic_op_type get_op();
    void add_val(const std::string&);
    void set_val_type(val_type v);
private:
    attr_val_pair avp;
    logic_op_type op;
};

