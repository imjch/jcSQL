#include "attr_val_pair.h"
#include <cassert>

attr_val_pair::attr_val_pair(const std::string& attr, result_list& list, val_type v_t)
:attr_name(attr), v_t(v_t), results(list)
{

}

attr_val_pair::attr_val_pair(const std::string& attr, const std::string& res, val_type v_t)
: attr_name(attr), v_t(v_t)
{
    results.add(res);
}


attr_val_pair::attr_val_pair()
:v_t(VAL_TYPE_INVALID)
{

}

attr_val_pair::~attr_val_pair()
{
}

void attr_val_pair::set_attr(const std::string& attr)
{
    assert(!attr.empty());
    attr_name = attr;
}
void attr_val_pair::set_val_type(val_type v)
{
    v_t = v;
}

void attr_val_pair::add_val(const std::string& val)
{
    assert(!val.empty());
    results.add(val);
}

void attr_val_pair::set_result_list(const result_list& list)
{
    results = list;
}

void attr_val_pair::set_result(const std::string& res)
{
    assert(!res.empty());
    if (results.size()==0)
    {
        results.add(res);
    }
    else
    {
        results[0] = res;
    }
}

const std::string& attr_val_pair::get_attr_name() const
{
    return attr_name;
}

val_type attr_val_pair::get_val_type()
{
    return v_t;
}

result_list& attr_val_pair::get_result_list()
{
    return results;
}

std::string& attr_val_pair::get_result()
{
    return results[0];
}

bool attr_val_pair::is_result_empty()
{
    return results.empty();
}
