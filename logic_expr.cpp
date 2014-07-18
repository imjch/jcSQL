#include "logic_expr.h"


logic_expr::logic_expr(const std::string& attr, const std::string& op, result_list& list, val_type vt) :
                  attr_name(attr),
                  op(op),
                  val_t(vt),
                  result(list)
{

}

logic_expr::~logic_expr()
{
}

void logic_expr::set_attr(const std::string& attr)
{
    attr_name = attr;
}
void logic_expr::set_op(const std::string& op)
{
    this->op = op;
}

void logic_expr::add_val(const std::string& val)
{
    result.add(val);
}

