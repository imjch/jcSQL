#pragma once
#include <string>
#include <unordered_map>
enum operators
{
    ADD=0,SUB,TIMES,SLASH
};

static std::string operators_to_s[] = {
    "+", "-", "*", "/"
};

static std::unordered_map<std::string,operators> oeprators_to_i= {
    { "+", ADD }, { "-", SUB }, { "*", TIMES } , {"/",SLASH}
};