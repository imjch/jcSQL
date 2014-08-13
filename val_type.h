#pragma once
#include <string>
#include <unordered_map>
enum val_type
{
    JC_INT = 0, JC_DOUBLE, JC_STRING, NULLABLE,VAL_TYPE_INVALID
};

const static std::string val_type_to_s[] = {
    "INT", "DOUBLE", "STRING","NULLABLE", "VAL_TYPE_INVALID"
};

const static std::unordered_map<std::string, val_type> val_type_to_i = {
    {"INT", JC_INT },
    {"DOUBLE",JC_DOUBLE},
    { "STRING",JC_STRING },
    { "NULLABLE", NULLABLE }
};