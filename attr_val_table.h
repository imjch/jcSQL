#pragma once
#include <map>
#include "attr_val_pair.h"

class attr_val_table
{
public:

    typedef std::map<std::string, attr_val_pair>::iterator iterator;
    attr_val_table();
    ~attr_val_table();
    void add_attr_val(attr_val_pair&);
    attr_val_pair get_attr_val(const std::string&);
    bool contain(const std::string&);
    iterator begin();
    iterator end();
    size_t size();
    bool empty();
private:
    std::map<std::string, attr_val_pair> map;
};

