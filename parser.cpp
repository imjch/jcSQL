#include "parser.h"
#include <stdexcept>
#include "operation_factory.h"
#include "log.h"
#include "err_msg_mgr.h"
parser::parser(lexer& lexer) :input(lexer), lookahead(input.next_token())
{
}


parser::~parser()
{
}

void parser::execute()
{
    stmts();
}

void parser::stmts()
{
    //switch (lookahead.get_token_type())
    //{

    ////default:
    ////    log::write_line(err_msg_mgr::invlid_expression("invalid type of operation %s", lookahead.to_string()).c_str());
    ////    return;
    //}
}


void parser::match(int x)
{
    if (lookahead.get_token_type() == x)
    {
        move();
    }
    else
    {
        log::write_line(err_msg_mgr::invlid_expression("expecting %s; found %s", lexer::get_token_name(x), lookahead.to_string()).c_str());
    }
}
void parser::move()
{
    lookahead = input.next_token();
}
