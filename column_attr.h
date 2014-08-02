#pragma once
#include <string>
enum column_attr
{
    NOT_NULL = 0, PRIMARY_KEY, UNIQUE,COLUMN_ATTR_INVALID
};

static std::string column_attrs[] = {
    "not null",
    "primary key",
    "unique"
};