#include "selection.h"

#include "lexer.h"
selection::selection() :processor(lexer::SELECT)
{
}


selection::~selection()
{
}
void selection::execute(){}
