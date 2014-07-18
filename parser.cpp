#include "parser.h"
#include <string>
#include <list>
#include "log.h"
#include <utility>
#include "err_msg_mgr.h"
#include "result_list.h"
#include "logic_expr.h"
#include "logic_expr_list.h"
#include "column_attr_table.h"
#include "column_attr_pair.h"
#include "select_operation.h"
#include "create_operation.h"
#include <utility>
parser::parser(lexer& lexer) :input(lexer), lookahead(input.next_token())
{
}

parser::~parser()
{
}

void parser::program()
{
    STMTS();
}

void parser::STMTS()
{
    switch (lookahead.get_token_type())
    {
    case tag::JC_SELECT:
        match(tag::JC_SELECT);
        SELECT();
        break;
    case tag::JC_ALTER:
        break;
    case tag::JC_CREATE:
        match(tag::JC_CREATE);
        CREATE();
        break;
    case tag::JC_DELETE:
        break;
    case tag::JC_DROP:
        break;
    case tag::JC_INSERT:
        break;
    default:
        log::write_line(err_msg_mgr::invlid_expression("invalid type of operation %s", lookahead.get_token_text().c_str()).c_str());
    }
}

select_operation parser::SELECT()
{
    match(tag::ARROW);
    select_operation select;
    select.set_table_name(TABLE_NAME());
    if (lookahead.get_token_type() == tag::IDENTIFIER)
    {
        select.add_cols(COLUMNS());
    }
    if (lookahead.get_token_type() == tag::LBRACKET)
    {
        select.add_logic_table(SELECTORS());
    }
    return select;
}

create_operation parser::CREATE()
{
    match(tag::ARROW);
    create_operation create;
    create.set_table_name(TABLE_NAME());
    create.set_type_column_table(TYPE_COLUMN_PAIRS());
    if (lookahead.get_token_type()==tag::LBRACKET)
    {
        SET_GLOBAL_COLUMN_ATTR_TABLE();
    }
    return create;
}
column_attr_pair parser::GET_COLUMN_ATTR_PAIR()
{
    std::string col = COLUMN();
    switch (lookahead.get_token_type())
    {
    case tag::NOT:
        match(tag::NOT);
        if (lookahead.get_token_type()==tag::JC_NULL)
        {
            match(tag::JC_NULL);
            return column_attr_pair(col,NOT_NULL);
        }
        else
        {
            goto error;
        }
    case tag::PRIMARY:
        match(tag::PRIMARY);
        if (lookahead.get_token_type()==tag::KEY)
        {
            match(tag::KEY);
            return column_attr_pair(col, PRIMARY_KEY);
        }
        else
        {
            goto error;
        }
        break;
    case tag::UNIQUE:
        match(tag::UNIQUE);
        return column_attr_pair(col, UNIQUE);
    error:
        log::write_line(err_msg_mgr::invlid_expression("invalid column attribution: %s", lookahead.get_token_text().c_str()).c_str());
    }
}
void parser::SET_GLOBAL_COLUMN_ATTR_TABLE()
{
    match(tag::LBRACKET);
    column_attr_table::add_column_attr(GET_COLUMN_ATTR_PAIR());
    while (lookahead.get_token_type()!=tag::RBRACKET)
    {
        match(tag::COMMA);
        column_attr_table::add_column_attr(GET_COLUMN_ATTR_PAIR());
    }
    match(tag::RBRACKET);
}

std::string parser::TABLE_NAME()
{
    return IDENTIFIER();
}

std::string parser::COLUMN()
{
    return IDENTIFIER();
}
std::string parser::TYPE()
{
    std::string type = VALUE();
    match(tag::BASIC_TYPE);
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
    match(tag::LOGIC_TYPE);
    return val;
}

result_list parser::COLUMNS()
{
    result_list cols;
    while (lookahead.get_token_type() == tag::IDENTIFIER)
    {
        cols.add(COLUMN());
    }
    return cols;
}

void parser::ATTR_VAL_PAIRS()
{

}

void parser::ATTR_VAL_PAIR()
{

}

type_column_pair parser::TYPE_COLUMN_PAIR()
{
    std::string type = TYPE();
    std::string col = COLUMN();
    return type_column_pair(type, col);
}

type_column_table parser::TYPE_COLUMN_PAIRS()
{
    type_column_table table;
    table.add_type_column(TYPE_COLUMN_PAIR());
    while (lookahead.get_token_type()==tag::BASIC_TYPE)
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
    if (lookahead.get_token_type() == tag::SINGLEQUOTE||
        lookahead.get_token_type() == tag::DOUBLEQUOTE)
    {
        val = GET_STRING_WITH_QUOTE();
        list.add(val);
        return logic_expr(attr_name, op, list, JC_STRING);
    }
    else if (lookahead.get_token_type()==tag::INT)
    {
        val = VALUE();
        match(tag::INT);
        list.add(val);
        return logic_expr(attr_name, op, list, JC_INT);
    }
    else if (lookahead.get_token_type() == tag::DOUBLE)
    {
        val = VALUE();
        match(tag::DOUBLE);
        list.add(val);
        return logic_expr(attr_name, op, list, JC_DOUBLE);
    }
    else
    {
        log::write_line(err_msg_mgr::invlid_expression("expecting the valid rvalue").c_str());
    }
}

logic_conn_table parser::LOGIC_EXPR_PAIRS()
{
    logic_conn_table table;
    logic_expr_list and_list;
    logic_expr_list or_list;
    table.add_logic_conn_list(std::make_pair(std::string("AND"), and_list));
    table.add_logic_conn_list(std::make_pair(std::string("OR"), or_list));
    logic_expr expr = LOGIC_EXPR_PAIR();

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
            log::write_line(err_msg_mgr::invlid_expression("expecting the valid logic connector : and / or ?").c_str());
        }
    }
    return table;
}

logic_conn_table parser::SELECTORS()
{
    match(tag::LBRACKET);
    logic_conn_table table;
    if (lookahead.get_token_type() != tag::RBRACKET)
    {
        table = LOGIC_EXPR_PAIRS();
    }
    else
    {
        log::write_line(err_msg_mgr::invlid_expression("expecting the logic expression").c_str());
    }
    match(tag::RBRACKET);
    return table;
}

void parser::match(int x)
{
    if (lookahead.get_token_type() == x)
    {
        move();
    }
    else
    {
        log::write_line(err_msg_mgr::invlid_expression("invalid identifier %s", lookahead.get_token_text().c_str()).c_str());
    }
}
void parser::move()
{
    lookahead = input.next_token();
}
