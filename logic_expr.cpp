#include "logic_expr.h"


logic_expr::logic_expr(const std::string& attr, logic_op_type op, result_list& list, val_type v_t) :
op(op)
{
    avp.set_attr(attr);
    avp.set_val_type(v_t);
    avp.set_result_list(list);
}
logic_expr::logic_expr()
{
    
}
logic_expr::~logic_expr()
{
}

std::string logic_expr::get_attr() const
{
    return avp.get_attr_name();
}

void logic_expr::set_attr(const std::string& attr)
{
    avp.set_attr(attr);
}

void logic_expr::set_op(logic_op_type op_type)
{
    op = op_type;
}

logic_op_type logic_expr::get_op()
{
    return op;
}

void logic_expr::add_val(const std::string& val)
{
    avp.add_val(val);
}

void logic_expr::set_val_type(val_type v)
{
    avp.set_val_type(v);
}

