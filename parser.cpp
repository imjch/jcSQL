#include "parser.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "log.h"
#include "err_msg_mgr.h"
parser::parser(lexer& lexer) :input(lexer), lookahead(input.next_token())
{
}

parser::~parser()
{
}

void parser::program()
{
   
}

void parser::stmts()
{

    switch (lookahead.get_token_type())
    {
    case tag::JC_SELECT:
        //match(tag::JC_SELECT);
        //SELECT();
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
    std::string table_name = TABLE_NAME();
    std::vector<std::string> cols=COLUMNS();
    if (lookahead.get_token_type()==tag::LBRACKET)
    {
        //SELECTORS();
    }
}

std::string parser::TABLE_NAME()
{
    return VALUE();
}

std::string parser::VALUE()
{
    std::string val = lookahead.get_token_text();
    match(tag::IDENTIFIER);
    return val;
}

std::vector<std::string> parser::COLUMNS()
{
    typedef std::vector<std::string> columns;
    columns cols;
    while (lookahead.get_token_type()==tag::IDENTIFIER)
    {
        cols.push_back(lookahead.get_token_text());
    }
    return cols;
}

void parser::SELECTORS()
{
    //todo:changed the return type
}

void parser::match(int x)
{
    if (lookahead.get_token_type() == x)
    {
        move();
    }
    else
    {
        log::write_line(err_msg_mgr::invlid_expression("expecting %s; found %s", lookahead.get_token_text().c_str(), lookahead.to_string()).c_str());
    }
}
void parser::move()
{
    lookahead = input.next_token();
}
