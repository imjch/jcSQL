#include "record_table.h"
#include <cassert>

record_table::record_table() :count(0)
{
}

record_table::~record_table()
{
}

bool record_table::contain(const primary_key_field& li)
{
    return index_table.count(li) > 0 ? true : false;
}

single_record record_table::get_record(primary_key_field& li)
{
    assert(index_table.count(li)>0);
    return records[index_table[li]].second;
}

void record_table::add_record(single_record& record)
{
    if (!contain(record.get_primary_key()))
    {
        index_table.insert(std::make_pair(record.get_primary_key(), count));
        records.push_back(std::make_pair(true, record));
        ++count;
    }
}

void record_table::remove_record(primary_key_field& li)
{
    records[index_table[li]].first = false;
}

std::list<single_record> record_table::get_all_records()
{
    std::list<single_record> record_list;
    for (size_t i = 0; i < records.size(); i++)
    {
        if (records[i].first)
          record_list.push_back(records[i].second);
    }
    return record_list;
}

