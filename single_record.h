#pragma once
#include "attr_val_table.h"
#include <string>
#include "primary_key.h"
class single_record
{
public:
    typedef attr_val_table::iterator iterator;
    single_record();
    //single_record(attr_val_table&);
    single_record(primary_key&, attr_val_table&);
    ~single_record();
    void set_primary_key(const primary_key&);
    primary_key& get_primary_key();
    void set_record(attr_val_table&);
    attr_val_table& get_record_data();
    iterator begin();
    iterator end();
private:
    primary_key key;
    attr_val_table record;
};

