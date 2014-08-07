#include "attr_val_table.h"
#include <utility>
attr_val_table::attr_val_table()
{
}

attr_val_table::~attr_val_table()
{
}

void attr_val_table::add_attr_val(attr_val_pair& pair)
{
    //map.insert(make_pair(pair.get_attr_name(),pair));
    map[pair.get_attr_name()] = pair;
}

attr_val_pair attr_val_table::get_attr_val(const std::string& attr_name)
{
    return map[attr_name];
}

attr_val_table::iterator attr_val_table::begin()
{
    return map.begin();
}

attr_val_table::iterator attr_val_table::end()
{
    return map.end();
}

size_t attr_val_table::size()
{
    return map.size();
}

bool attr_val_table::empty()
{
    return map.empty();
}