#pragma once
#include "attr_val_table.h"
#include <string>
class single_record
{
public:
    typedef attr_val_table::iterator iterator;
    single_record();
    single_record(const std::string&, attr_val_table&);
    ~single_record();
    void set_primary_key(const std::string&);
    const std::string& get_primary_key();
    void set_record(attr_val_table&);
    attr_val_table& get_record_data();
    iterator begin();
    iterator end();
private:
    std::string primary_key;
    attr_val_table record;
};

