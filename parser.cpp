#include "parser.h"
#include <string>
#include <list>
#include "log.h"
#include <utility>
#include "err_msg_mgr.h"
#include "result_list.h"
#include "logic_expr.h"
#include "select_operation.h"
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
    case tag::JC_ALTER:

    case tag::JC_CREATE:

    case tag::JC_DELETE:

    case tag::JC_DROP:

    case tag::JC_INSERT:

    default:
        log::write_line(err_msg_mgr::invlid_expression("invalid type of operation %s", lookahead.get_token_text()).c_str());
    }
}

void parser::SELECT()
{
    match(tag::ARROW);
    select_operation select;
    select.add_table_name(TABLE_NAME());
    if (lookahead.get_token_type() == tag::IDENTIFIER)
    {
        select.add_cols(COLUMNS());
    }
    if (lookahead.get_token_type() == tag::LBRACKET)
    {
        select.add_table(SELECTORS());
    }
    else
    {
        log::write_line(err_msg_mgr::invlid_expression("invalid identifier %s", lookahead.get_token_text()).c_str());
    }
}

std::string parser::TABLE_NAME()
{
    return IDENTIFIER();
}

std::string parser::COLUMN()
{
    return IDENTIFIER();
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

std::string parser::GET_STRING_WITH_QUOTE()
{
    std::string str;
    if (lookahead.get_token_type()==tag::SINGLEQUOTE)
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
        log::write_line(err_msg_mgr::invlid_expression("invalid identifier %s",lookahead.get_token_text()).c_str());
    }
}
void parser::move()
{
    lookahead = input.next_token();
}
