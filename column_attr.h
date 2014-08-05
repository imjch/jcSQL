#pragma once
#include <string>
#include <unordered_map>
enum column_attr
{
    NOT_NULL = 0, PRIMARY_KEY, UNIQUE,COLUMN_ATTR_INVALID
};
const static std::unordered_map<std::string, column_attr> column_attrs_to_i = { 
    { "not null", NOT_NULL }, 
    { "primary key", PRIMARY_KEY }, 
    { "unique", UNIQUE } };
const static std::string column_attrs_to_s[] = {
    "not null",
    "primary key",
    "unique"
};

