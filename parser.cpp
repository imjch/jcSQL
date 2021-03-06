#include "parser.h"
#include <string>
#include <list>
#include "err_collector.h"
#include <stdarg.h>
#include "err_msg_mgr.h"
#include "result_list.h"
#include "logic_expr.h"
#include "logic_expr_list.h"
#include "table_attr.h"
#include "column_attr_pair.h"
#include "select_operation.h"
#include "create_operation.h"
#include <utility>
#include "alter_operation.h"
#include "operators.h"
#include "logic_op_type.h"
parser::parser(lexer& lexer) :input(lexer), lookahead(input.next_token())
{
}

parser::~parser()
{
}

operation* parser::program()
{
    return STMTS();
}

operation* parser::STMTS()
{
    switch (lookahead.get_token_type())
    {
    case tag::JC_SELECT:
        match(tag::JC_SELECT);
        return JC_SELECT();
        break;
    case tag::JC_ALTER:
        match(tag::JC_ALTER);
        return JC_ALTER();
        break;
    case tag::JC_CREATE:
        match(tag::JC_CREATE);
        return JC_CREATE();
        break;
    case tag::JC_DELETE:
        match(tag::JC_DELETE);
        return JC_DELETE();
        break;
    case tag::JC_DROP:
        match(tag::JC_DROP);
        return JC_DROP();
        break;
    case tag::JC_INSERT:
        match(tag::JC_INSERT);
        return JC_INSERT();
        break;
    default:
        err_collector::add_error(err_msg_mgr::invalid_expression("invalid type of operation %s", lookahead.get_token_text().c_str()));
        return nullptr;
    }
}

void parser::VERIFY_END()
{
    if (lookahead.get_token_type() != tag::EOF_TYPE)
    {
        err_collector::add_error(err_msg_mgr::invalid_expression("invalid identifier %s", lookahead.get_token_text().c_str()));
    }
}

select_operation* parser::JC_SELECT()
{
    match(tag::ARROW);
    select_operation select;
    std::string table_name = TABLE_NAME();
    std::list<std::string> list;
    logic_conn_table table;
    if (lookahead.get_token_type() == tag::IDENTIFIER)
    {
        list = COLUMNS();
    }
    if (lookahead.get_token_type() == tag::LBRACKET)
    {
        table = SELECTORS();
    }
    VERIFY_END();
    return new select_operation(table_name, list, table);
}

create_operation* parser::JC_CREATE()
{
    match(tag::ARROW);
    std::string table_name = TABLE_NAME();
    type_column_list t_c_table = TYPE_COLUMN_PAIRS();
    table_attr t_attr;
    if (lookahead.get_token_type() == tag::LBRACKET)
    {
        t_attr=GET_TABLE_ATTR();
    }
    VERIFY_END();
    return new create_operation(table_name, t_c_table,t_attr);
}

drop_operation* parser::JC_DROP()
{
    match(tag::ARROW);
    std::string t_name = TABLE_NAME();
    VERIFY_END();
    return new drop_operation(t_name);
}

alter_operation* parser::JC_ALTER()
{
    match(tag::ARROW);
    operators op;
    std::string table_name = TABLE_NAME();
    switch (lookahead.get_token_type())
    {
    case tag::ADD:
        op = ADD;
        match(tag::ADD);
        break;
    case tag::SUB:
        match(tag::SUB);
        op = SUB;
        break;
    case tag::SLASH:
        match(tag::SLASH);
        op = SLASH;
        break;
    default:
        move();
        err_collector::add_error(err_msg_mgr::invalid_expression("invalid operator type %s",lookahead.get_token_text().c_str()));
    }
    type_column_list table = TYPE_COLUMN_PAIRS();
    VERIFY_END();
    return new alter_operation(table_name,op, table);
}

delete_operation* parser::JC_DELETE()
{
    match(tag::ARROW);
    std::string table_name = TABLE_NAME();
    logic_conn_table table;
    if (lookahead.get_token_type() == tag::LBRACKET)
    {
        table = SELECTORS();
    }
    VERIFY_END();
    return new delete_operation(table_name, table);
}
insert_operation* parser::JC_INSERT()
{
    match(tag::ARROW);
    std::string table_name = TABLE_NAME();
    attr_val_table list;
    if (lookahead.get_token_type() != tag::EOF_TYPE)
    {
        list = (ATTR_VAL_PAIRS());
    }
    VERIFY_END();
    return new insert_operation(table_name, list);
}

column_attr_pair parser::GET_COLUMN_ATTR_PAIR()
{
    std::string col = COLUMN();
    switch (lookahead.get_token_type())
    {
    case tag::NOT:
        match(tag::NOT);
        if (lookahead.get_token_type() == tag::JC_NULL)
        {
            match(tag::JC_NULL);
            return column_attr_pair(NOT_NULL,col);
        }
        else
        {
            goto error;
        }
    case tag::PRIMARY:
        match(tag::PRIMARY);
        if (lookahead.get_token_type() == tag::KEY)
        {
            match(tag::KEY);
            return column_attr_pair(PRIMARY_KEY,col);
        }
        else
        {
            goto error;
        }
        break;
    case tag::UNIQUE:
        match(tag::UNIQUE);
        return column_attr_pair(UNIQUE,col );
    default:
    error:
        err_collector::add_error(err_msg_mgr::invalid_expression("invalid column attribution: %s", lookahead.get_token_text().c_str()));
        move();
        return column_attr_pair(COLUMN_ATTR_INVALID,col );
    }
}
table_attr parser::GET_TABLE_ATTR()
{
    match(tag::LBRACKET);
    table_attr t_attr;
    t_attr.add_column_attr(GET_COLUMN_ATTR_PAIR());
    while (lookahead.get_token_type() != tag::RBRACKET&&lookahead.get_token_type()!=tag::EOF_TYPE)
    {
        match(tag::COMMA);
        t_attr.add_column_attr(GET_COLUMN_ATTR_PAIR());
    }
    match(tag::RBRACKET);
    return t_attr;
}

std::string parser::TABLE_NAME()
{
    return IDENTIFIER();
}

std::string parser::COLUMN()
{
    std::string id = VALUE();
    match(tag::IDENTIFIER,"invalid column name %s,expecting valid column name",lookahead.get_token_text().c_str());
    return id;
}
std::string parser::TYPE()
{
    std::string type = VALUE();
    match(tag::BASIC_TYPE,"invalid type: %s",lookahead.get_token_text().c_str());
    return type;
}
std::string parser::IDENTIFIER()
{
    std::string id = VALUE();
    match(tag::IDENTIFIER);
    return id;
}

std::string parser::VALUE()
{
    return lookahead.get_token_text();
}

std::string parser::ATTR_NAME()
{
    return IDENTIFIER();
}

std::string parser::OP()
{
    std::string val = VALUE();
    match(tag::LOGIC_TYPE, "invalid type of err_collectorical operator: %s", lookahead.get_token_text().c_str());
    return val;
}

std::list<std::string> parser::COLUMNS()
{
    std::list<std::string> cols;
    while (lookahead.get_token_type() == tag::IDENTIFIER)
    {
        cols.push_back(COLUMN());
    }
    return cols;
}

attr_val_table parser::ATTR_VAL_PAIRS()
{
    attr_val_table list;
    while (lookahead.get_token_type() == tag::IDENTIFIER)
    {
        list.add_attr_val(ATTR_VAL_PAIR());
    }
    return list;
}

attr_val_pair parser::ATTR_VAL_PAIR()
{
    std::string attr_name = ATTR_NAME();
    match(tag::ASSIGN);
    result_list list;
    std::string val;
    if (lookahead.get_token_type() == tag::SINGLEQUOTE ||
        lookahead.get_token_type() == tag::DOUBLEQUOTE)
    {
        val = GET_STRING_WITH_QUOTE();
        list.add(val);
        return attr_val_pair(attr_name, list, JC_STRING);
    }
    else if (lookahead.get_token_type() == tag::DOUBLE)
    {
        val = VALUE();
        match(tag::DOUBLE);
        list.add(val);
        return attr_val_pair(attr_name, list, JC_DOUBLE);
    }
    else if (lookahead.get_token_type() == tag::INT)
    {
        val = VALUE();
        match(tag::INT);
        list.add(val);
        return attr_val_pair(attr_name, list, JC_INT);
    }
    else
    {
        err_collector::add_error(err_msg_mgr::invalid_expression("invalid rvalue %s , expecting the valid rvalue",lookahead.get_token_text().c_str()));
        move();
    }
    return attr_val_pair(attr_name, list, VAL_TYPE_INVALID);
}

type_column_pair parser::TYPE_COLUMN_PAIR()
{
    std::string type = TYPE();
    std::string col = COLUMN();
    return type_column_pair(val_type_to_i.at(type), col);
}

type_column_list parser::TYPE_COLUMN_PAIRS()
{
    type_column_list table;
    table.add_type_column(TYPE_COLUMN_PAIR());
    while (lookahead.get_token_type() == tag::BASIC_TYPE)
    {
        table.add_type_column(TYPE_COLUMN_PAIR());
    }
    return table;
}

std::string parser::GET_STRING_WITH_QUOTE()
{
    std::string str;
    if (lookahead.get_token_type() == tag::SINGLEQUOTE)
    {
        match(tag::SINGLEQUOTE);
        str = VALUE();
        match(tag::STRING);
        match(tag::SINGLEQUOTE);
    }
    else
    {
        match(tag::DOUBLEQUOTE);
        str = VALUE();
        match(tag::STRING);
        match(tag::DOUBLEQUOTE);
    }
    return str;
}

logic_expr parser::LOGIC_EXPR_PAIR()
{
    std::string attr_name = ATTR_NAME();
    std::string op = OP();
    std::string val;
    result_list list;
    if (lookahead.get_token_type() == tag::SINGLEQUOTE ||
        lookahead.get_token_type() == tag::DOUBLEQUOTE)
    {
        val = GET_STRING_WITH_QUOTE();
        list.add(val);
        return logic_expr(attr_name, logic_op_type_s_to_i[op], list, JC_STRING);
    }
    else if (lookahead.get_token_type() == tag::INT)
    {
        val = VALUE();
        match(tag::INT);
        list.add(val);
        return logic_expr(attr_name, logic_op_type_s_to_i[op], list, JC_INT);
    }
    else if (lookahead.get_token_type() == tag::DOUBLE)
    {
        val = VALUE();
        match(tag::DOUBLE);
        list.add(val);
        return logic_expr(attr_name, logic_op_type_s_to_i[op], list, JC_DOUBLE);
    }
    else
    {
        err_collector::add_error(err_msg_mgr::invalid_expression("expecting the valid rvalue").c_str());
        move();
    }
    return logic_expr();
}

//maybe this method need refactoring...:p
logic_conn_table parser::LOGIC_EXPR_PAIRS()
{
    logic_conn_table table;
    logic_expr_list and_list;
    logic_expr_list or_list;
    logic_expr expr = LOGIC_EXPR_PAIR();

    if (lookahead.get_token_type() != tag::IDENTIFIER)
    {
        and_list.add_logic_expr(expr);
        table.add_logic_expr_list(AND, and_list);
        table.add_logic_expr_list(OR, or_list);
        return table;
    }
    switch (lookahead.get_token_type())
    {
    case tag::AND:
        and_list.add_logic_expr(expr);
        break;
    case tag::OR:
        or_list.add_logic_expr(expr);
        break;
    }

    while (lookahead.get_token_type() != tag::RBRACKET)
    {
        switch (lookahead.get_token_type())
        {
        case tag::AND:
            match(tag::AND);
            and_list.add_logic_expr(LOGIC_EXPR_PAIR());
            break;
        case tag::OR:
            match(tag::OR);
            or_list.add_logic_expr(LOGIC_EXPR_PAIR());
            break;
        default:
            err_collector::add_error(err_msg_mgr::invalid_expression("expecting the valid err_collectoric connector : and / or ?").c_str());
            move();
        }
    }
    table.add_logic_expr_list(AND, and_list);
    table.add_logic_expr_list(OR, or_list);
    return table;
}

logic_conn_table parser::SELECTORS()
{
    match(tag::LBRACKET, "invalid identifier %s, expecting token '['",lookahead.get_token_text().c_str());
    logic_conn_table table;
    if (lookahead.get_token_type() != tag::RBRACKET)
    {
        table =LOGIC_EXPR_PAIRS();
    }
    else
    {
        err_collector::add_error(err_msg_mgr::invalid_expression("expecting the err_collectoric expression"));
        move();
    }
    match(tag::RBRACKET, "invalid identifier %s, expecting token ']'", lookahead.get_token_text().c_str());
    return table;
}

void parser::match(int x)
{
    match(x,"invalid identifier: %s",lookahead.get_token_text().c_str());
}

void parser::match(int x, char* format, ...)
{
    if (lookahead.get_token_type() == x)
    {
        move();
    }
    else
    {
        err_collector::add_error(err_msg_mgr::invalid_expression(format, lookahead.get_token_text().c_str()));
        move();
    }
}

void parser::move()
{
    lookahead = input.next_token();
}
