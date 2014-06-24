
#include "lexer.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include <memory>

const std::string lexer::token_names[] = { "N/A","<EOF>","NAME","SINGLEQUOTE","DOUBLEQUOTE","COMMA","LBRACK"
										   ,"RBRACK"};

token::token(int type, const char* text) :type(type), text(text)
{

}

token::~token()
{

}
int token::get_token_type()
{
    return type;
}

const std::string lexer::get_token_name(int type)
{
    return token_names[type];
}

void lexer::WS()
{
    while (c==' '||c=='\t'||c=='\n'||c=='\r')
    {
        consume();
    }
}
token lexer::TNAME()
{
    std::string buf;
    do
    {
        buf.push_back(c);
        consume();
    } while (isalpha(c));
    return token(NAME, buf.c_str());
}

token lexer::next_token()
{
    while (c!=EOF)
    {
        switch (c)
        {
        case ' ':case '\t':case '\n':case '\r':
            WS();
            continue;
        case '\'':
            consume();
            return token(SINGLEQUOTE, "'");
        case '"':
            consume();
            return token(DOUBLEQUOTE, "\"");
        case ',':
            consume();
            return token(COMMA, ",");
        case '(':
            consume();
            return token(LPARENTHESIS, "(");
        case ')':
            consume();
            return token(RPARENTHESIS, ")");
        default:
            if (isalpha(c))
            {
                return TNAME();
            }
            std::string error_msg("invalid character: ");
            error_msg.push_back(c);
            throw new std::runtime_error(error_msg);
        }
    }
    return token(EOF_TYPE, "<EOF>");
}

lexer::lexer(const std::string& input = "") : input(input), c(input[0]), p(0)
{

}

lexer::~lexer()
{

}

const std::string& token::to_string()
{
     text.insert(0, "<'").append("',").append(lexer::get_token_name(type)).push_back('>');
     return text;
}

void lexer::consume()
{
    ++p;
    if (p>=input.size())
    {
        c = EOF;
    }
    else
    {
        c = input[p];
    }
}
void lexer::match(char x)
{
    if (c==x)
    {
        consume();
    }
    else
    {
        std::string error_msg("expecting ");
        error_msg.push_back(x);
        error_msg.append("; found ");
        error_msg.push_back(c);
        throw std::runtime_error(error_msg);
    }
}



