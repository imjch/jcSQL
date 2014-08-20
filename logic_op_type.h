#pragma once
#include <unordered_map>
#include <string>
enum logic_op_type
{
    GT = 0, LT, GE, LE, EQ, NE
};

static std::unordered_map<std::string, logic_op_type> logic_op_type_s_to_i = {
    { ">", GT },
    { "<", LT },
    { ">=", GE },
    { "<=", LE },
    { "==", EQ },
    { "!=", NE },
};
static std::string logic_op_type_i_to_s[] = {
    ">",
    "<",
    ">=",
    "<=",
    "==",
    "!=",
};

