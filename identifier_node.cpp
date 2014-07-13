#include "identifier_node.h"


identifier_node::identifier_node(const std::string& str) :identifier(str)
{
}


identifier_node::~identifier_node()
{
}
std::string identifier_node::eval()
{
    return identifier;
}
