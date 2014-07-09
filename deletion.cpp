#include "deletion.h"

#include "lexer.h"
deletion::deletion() :processor(lexer::DELETE)
{
}


deletion::~deletion()
{
}

void deletion::execute(){}