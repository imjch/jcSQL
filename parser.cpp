#include "parser.h"
#include <stdexcept>
#include <cassert>
parser::parser(lexer& lexer) :input(lexer), lookahead(input.next_token())
{
}


parser::~parser()
{
}

void parser::list()
{
    match(lexer::LPARENTHESIS);
    elements();
    match(lexer::RPARENTHESIS);
}

void parser::elements()
{
    element();
    while (lookahead.get_token_type()==lexer::COMMA)
    {
        match(lexer::COMMA);
        element();
    }
}

void parser::element()
{
    if (lookahead.get_token_type()==lexer::NAME)
    {
        match(lexer::NAME);
    }
    else if (lookahead.get_token_type()==lexer::LPARENTHESIS)
    {
        list();
    }
    else
    {
        std::string err_msg("expecting name or list£»found");
        err_msg.append((lookahead.to_string()));
        throw std::runtime_error(err_msg);
    }
}

void parser::match(int x)
{
    if (lookahead.get_token_type() == x)
    {
        consume();
    }
    else
    {
        std::string error_msg("expecting ");
        error_msg.append(lexer::get_token_name(x)).append("; found ").append(lookahead.to_string());
        throw std::runtime_error(error_msg);
    }
}
void parser::consume()
{
    lookahead = input.next_token();
}
