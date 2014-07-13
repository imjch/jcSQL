#pragma once
#include <string>
#include "expr_astree.h"
class identifier_node
{
public:
    identifier_node(const std::string&);
    ~identifier_node();
    std::string eval();
private:
    std::string identifier;
};

