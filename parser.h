#pragma once
#include "lexer.h"
class parser
{
public:
    parser(lexer&);
    ~parser();
    void execute();
    void stmts();
   
private:
    void match(int);
    void move();
    lexer input;
    token lookahead;
};

