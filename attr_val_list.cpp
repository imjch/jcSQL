#include "attr_val_list.h"


attr_val_list::attr_val_list()
{
}

attr_val_list::~attr_val_list()
{
}

void attr_val_list::add_attr_val(const attr_val_pair& pair)
{
    list.push_back(pair);
}
