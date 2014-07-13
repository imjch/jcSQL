#pragma once
#include "lexer.h"
#include <vector>
#include "op_tree.h"

class parser
{
public:
    parser(lexer&);
    ~parser();
    void program();
    void stmts();
   
    void SELECT();
    std::string VALUE();
    std::string TABLE_NAME();
    std::vector<std::string> COLUMNS();
    void SELECTORS();
private:
    void match(int);
    void move();
    lexer input;
    token lookahead;
};

