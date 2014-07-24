#include "logic_expr.h"


logic_expr::logic_expr(const std::string& attr, const std::string& op, result_list& list, val_type v_t):
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

void logic_expr::set_attr(const std::string& attr)
{
    avp.set_attr(attr);
}

void logic_expr::set_op(const std::string& op)
{
    this->op = op;
}

void logic_expr::add_val(const std::string& val)
{
    avp.add_val(val);
}

