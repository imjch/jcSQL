#include "attr_val_pair.h"


attr_val_pair::attr_val_pair(const std::string& attr, result_list& list, val_type v_t)
:attr_name(attr), v_t(v_t), result(list)
{
}

attr_val_pair::attr_val_pair()
{

}

attr_val_pair::~attr_val_pair()
{
}

void attr_val_pair::set_attr(const std::string& attr)
{
    attr_name = attr;
}
void attr_val_pair::set_val_type(val_type v)
{
    v_t = v;
}
void attr_val_pair::add_val(const std::string& val)
{
    result.add(val);
}

void attr_val_pair::set_result_list(const result_list& list)
{
    result = list;
}

std::string attr_val_pair::get_attr_name()
{
    return attr_name;
}

val_type attr_val_pair::get_val_type()
{
    return v_t;
}

result_list attr_val_pair::get_result_list()
{
    return result;
}

