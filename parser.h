#pragma once
#include "lexer.h"
#include <vector>
#include "err_collector.h"
#include "logic_expr.h"
#include "logic_expr_list.h"
#include "logic_conn_table.h"
#include "type_column_pair.h"
#include "type_column_list.h"
#include "table_attr.h"
#include "column_attr_pair.h"
#include "select_operation.h"
#include "create_operation.h"
#include "drop_operation.h"
#include "insert_operation.h"
#include "delete_operation.h"
#include "alter_operation.h"
#include <utility>
class parser
{
public:
    parser(lexer&);
    ~parser();
    operation* program();
private:
    operation* STMTS();
    std::string GET_STRING_WITH_QUOTE();
    std::pair<int, std::string> REAL_VALUE();
    std::string OP();
    std::list<std::string> COLUMNS();
    column_attr_pair GET_COLUMN_ATTR_PAIR();
    table_attr GET_TABLE_ATTR();
    logic_conn_table SELECTORS();
    type_column_pair TYPE_COLUMN_PAIR();
    type_column_list TYPE_COLUMN_PAIRS();
    attr_val_pair ATTR_VAL_PAIR();
    attr_val_table ATTR_VAL_PAIRS();
    logic_expr LOGIC_EXPR_PAIR();
    logic_conn_table LOGIC_EXPR_PAIRS();
    std::string TABLE_NAME();
    std::string VALUE();
    std::string ATTR_NAME();
    std::string COLUMN();
    std::string TYPE();
    std::string IDENTIFIER();
    void match(int);
    void match(int, char* format, ...);
    void move();
    void VERIFY_END();

    drop_operation* JC_DROP();
    delete_operation* JC_DELETE();
    select_operation* JC_SELECT();
    create_operation* JC_CREATE();
    insert_operation* JC_INSERT();
    alter_operation* JC_ALTER();
    lexer input;
    token lookahead;
};

