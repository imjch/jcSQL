#include "attr_val_list.h"
#include <utility>
attr_val_list::attr_val_list()
{
}

attr_val_list::~attr_val_list()
{
}

void attr_val_list::add_attr_val(attr_val_pair& pair)
{
    map.insert(make_pair(pair.get_attr_name(),pair));
}

attr_val_pair attr_val_list::get_attr_val(const std::string& attr_name)
{
    return map[attr_name];
}

attr_val_list::iterator attr_val_list::begin()
{
    return map.begin();
}

attr_val_list::iterator attr_val_list::end()
{
    return map.end();
}

size_t attr_val_list::size()
{
    return map.size();
}