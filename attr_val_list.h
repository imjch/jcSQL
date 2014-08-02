#pragma once
#include <unordered_map>
#include "attr_val_pair.h"
class attr_val_list
{
public:
    typedef std::unordered_map<std::string, attr_val_pair>::iterator iterator;
    attr_val_list();
    ~attr_val_list();
    void add_attr_val(attr_val_pair&);
    attr_val_pair get_attr_val(const std::string&);
    iterator begin();
    iterator end();
    size_t size();
private:
    std::unordered_map<std::string,attr_val_pair> map;
};

