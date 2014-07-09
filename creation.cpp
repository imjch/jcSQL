#include "creation.h"
#include "lexer.h"
creation::creation() :processor(lexer::CREATE)
{
}

creation::~creation()
{
}

void creation::execute(){}
