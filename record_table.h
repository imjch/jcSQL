#pragma once
#include <vector>
#include <unordered_map>
#include "attr_val_table.h"
#include <list>
#include <string>
#include <utility>

class record_table
{
public:
    typedef int key_index;
    typedef std::string primary_key_field;
    record_table();
    ~record_table();
    bool contain(primary_key_field&);
    attr_val_table get_record(primary_key_field&);
    void add_record(primary_key_field&, attr_val_table&);
    void remove_record(primary_key_field&);
private:
    std::vector<std::pair<bool,attr_val_table>> records;
    std::unordered_map<primary_key_field, key_index> index_table;
    size_t count;
};

