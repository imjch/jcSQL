#pragma once
#include "lexer.h"
#include <vector>
#include "logic_expr.h"
#include "logic_expr_list.h"
#include "logic_conn_table.h"
#include <utility>
class parser
{
public:
    typedef std::pair<std::string, std::string> attr_val_pair;
    typedef std::vector<attr_val_pair> attr_val_pairs;
    parser(lexer&);
    ~parser();
    void program();
private:
    std::string GET_STRING_WITH_QUOTE();
    std::pair<int, std::string> REAL_VALUE();
    std::string OP();
    result_list COLUMNS();
    logic_conn_table SELECTORS();
    void ATTR_VAL_PAIR();
    logic_expr LOGIC_EXPR_PAIR();
    void ATTR_VAL_PAIRS();
    logic_conn_table LOGIC_EXPR_PAIRS();
    void STMTS();
    void SELECT();
    std::string TABLE_NAME();
    std::string VALUE();
    std::string ATTR_NAME();
    std::string COLUMN();
    std::string IDENTIFIER();
    void match(int);
    void move();
    
    lexer input;
    token lookahead;
};

