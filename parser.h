#pragma once
#include "lexer.h"
#include <vector>
#include "logic_expr.h"
#include "logic_expr_list.h"
#include "logic_conn_table.h"
#include "type_column_pair.h"
#include "type_column_table.h"
#include "column_attr_table.h"
#include "column_attr_pair.h"
#include "select_operation.h"
#include "create_operation.h"
#include <utility>
class parser
{
public:
    parser(lexer&);
    ~parser();
    void program();
private:
    std::string GET_STRING_WITH_QUOTE();
    std::pair<int, std::string> REAL_VALUE();
    std::string OP();
    result_list COLUMNS();
    column_attr_pair GET_COLUMN_ATTR_PAIR();
    void SET_GLOBAL_COLUMN_ATTR_TABLE();
    logic_conn_table SELECTORS();
    type_column_pair TYPE_COLUMN_PAIR();
    type_column_table TYPE_COLUMN_PAIRS();
    void ATTR_VAL_PAIR();
    void ATTR_VAL_PAIRS();
    logic_expr LOGIC_EXPR_PAIR();
    logic_conn_table LOGIC_EXPR_PAIRS();
    void STMTS();
    select_operation SELECT();
    create_operation CREATE();
    std::string TABLE_NAME();
    std::string VALUE();
    std::string ATTR_NAME();
    std::string COLUMN();
    std::string TYPE();
    std::string IDENTIFIER();
    void match(int);
    void move();
    
    lexer input;
    token lookahead;
};

