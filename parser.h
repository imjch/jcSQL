#pragma once
#include "lexer.h"
class parser
{
public:
    parser(lexer&);
    ~parser();
    void execute();
    void elements();
    void element();
private:
    void match(int);
    void consume();
    lexer input;
    token lookahead;
};

