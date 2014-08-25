#include "single_record.h"


single_record::single_record()
{
}

//single_record::single_record(const std::string& key, attr_val_table& a_v_table)
//:primary_key(key),
//record(a_v_table)
//{
//}

single_record::single_record(primary_key& key,attr_val_table& a_v_table)
:record(a_v_table), key(key)
{
}

single_record::~single_record()
{
}

void single_record::set_primary_key(const primary_key& k)
{
    key=k;
}

void single_record::set_record(attr_val_table& a_v_table)
{
    record = a_v_table;
}

primary_key& single_record::get_primary_key()
{
    return key;
}

attr_val_table& single_record::get_record_data()
{
    return record;
}

 single_record::iterator single_record::begin()
 {
     return record.begin();
 }

 single_record::iterator single_record::end()
 {
     return record.end();
 }
