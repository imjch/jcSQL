#include "record_table.h"
#include <cassert>

record_table::record_table() :count(0)
{
}


record_table::~record_table()
{
}

bool record_table::contain(primary_key_field& li)
{
    return index_table.count(li) > 0 ? true : false;
}

attr_val_table record_table::get_record(primary_key_field& li)
{
    assert(index_table.count(li)>0);
    return records[index_table[li]].second;
}

void record_table::add_record(primary_key_field& li, attr_val_table& a_v_table)
{
    if (!contain(li))
    {
        index_table.insert(std::make_pair(li, count));
        records.push_back(std::make_pair(true, a_v_table));
        ++count;
    }
}

void record_table::remove_record(primary_key_field& li)
{
    records[index_table[li]].first = false;
}