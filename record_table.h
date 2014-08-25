#pragma once
#include <vector>
#include <unordered_map>
#include "attr_val_table.h"
#include <list>
#include <string>
#include <utility>
#include "logic_expr.h"
#include "logic_expr_list.h"
#include "logic_conn_table.h"
#include "single_record.h"
#include "primary_key.h"
class record_table
{
public:
    typedef int key_index;
    typedef std::string primary_key_field;
    record_table();
    ~record_table();
    bool contain(primary_key&);
    single_record get_record(primary_key&);
    std::list<single_record> get_records(logic_conn_table&);
    void add_record(single_record&);
    void remove_record(primary_key&);
    void remove_record(logic_conn_table&);
    std::list<single_record> get_all_records();
private:

    std::list<single_record> GT_FILTER(attr_val_pair&);
    std::list<single_record> LT_FILTER(attr_val_pair&);
    std::list<single_record> GE_FILTER(attr_val_pair&);
    std::list<single_record> LE_FILTER(attr_val_pair&);
    std::list<single_record> EQ_FILTER(attr_val_pair&);
    std::list<single_record> NE_FILTER(attr_val_pair&);
    std::vector<std::pair<bool,single_record>> records;
    std::unordered_map<primary_key_field, key_index> index_table;
    size_t count;
};

