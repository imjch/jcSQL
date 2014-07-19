#pragma once
#include <list>
#include "attr_val_pair.h"
class attr_val_list
{
public:
    attr_val_list();
    ~attr_val_list();
    void add_attr_val(const attr_val_pair&);
private:
    std::list<attr_val_pair> list;
};

