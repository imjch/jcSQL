#include "parser.h"
#include <stdexcept>
#include "processor_factory.h"

parser::parser(lexer& lexer) :input(lexer), lookahead(input.next_token())
{
}


parser::~parser()
{
}

void parser::execute()
{
    //todo
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
    if (lookahead.get_token_type() == lexer::IDENTIFIER)
    {
        match(lexer::IDENTIFIER);
    }
    else if (lookahead.get_token_type() == lexer::LBRACKET)
    {
        //todo
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
