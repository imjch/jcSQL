#pragma once
#include <string>
enum val_type
{
    JC_INT = 0, JC_DOUBLE, JC_STRING,VAL_TYPE_INVALID
};

static std::string val_types[] = {
    "int", "double", "string", "invalid_val_type"
};