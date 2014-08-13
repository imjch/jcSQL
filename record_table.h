#pragma once
#include <vector>
#include <unordered_map>
#include "attr_val_table.h"
#include <list>
#include <string>
#include <utility>
#include "single_record.h"

class record_table
{
public:
    typedef int key_index;
    typedef std::string primary_key_field;
    record_table();
    ~record_table();
    bool contain(const primary_key_field&);
    single_record get_record(primary_key_field&);
    void add_record(single_record&);
    void remove_record(primary_key_field&);
    std::list<single_record> get_all_records();
private:
    std::vector<std::pair<bool,single_record>> records;
    std::unordered_map<primary_key_field, key_index> index_table;
    size_t count;
};

