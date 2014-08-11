#pragma once
#include "type_column_pair.h"
#include <map>
#include <string>

class type_column_list
{
public:
    typedef std::map<std::string,type_column_pair>::iterator iterator;
    type_column_list();
    ~type_column_list();
    void add_type_column(const type_column_pair&);
    void add_type_column(iterator&, iterator&);
    void remove_type_column(const type_column_pair&);
    void remove_type_column(iterator& begin, iterator& end);
    void alter_column_type(const type_column_pair& pair);
    void alter_column_type(iterator&, iterator&);
    type_column_pair get_type_column_pair(const std::string&);
    bool contain(const std::string&);
    
    size_t size();
    iterator begin();
    iterator end();
    bool empty();
private:
    std::map<std::string,type_column_pair> items;
};

