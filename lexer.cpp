#include "lexer.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include "processor.h"
#include "log.h"
#include "err_msg_mgr.h"

const std::string lexer::token_names[] = {
    "N/A","<EOF>","IDENTIFIER","SINGLEQUOTE",
    "DOUBLEQUOTE","COMMA","LBRACKET",
    "RBRACKET","LESSOP","MOREOP","LEOP",
    "MEOP","NEOP","EQOP","NUM","CHARS",
    "ARROW","STRING"};

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

const std::string& token::to_string()
{
    text.insert(0, "<'").append("',").append(lexer::get_token_name(type)).push_back('>');
    return text;
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
token lexer::IDENTIFIERS()
{
    std::string buf;
    do
    {
        buf.push_back(c);
        consume();
    } while (isalnum(c));

    return token(IDENTIFIER, buf.c_str());
}

token lexer::NUMS()
{
    std::string buf;
    do
    {
        buf.push_back(c);
        consume();
    } while (isnum(c));
    if (c == '.')
    {
        do
        {
            buf.push_back(c);
            consume();
        } while (isnum(c));
    }
    return token(lexer::NUM, buf.c_str());
}

//token lexer::STRINGS_WITH_SINGLEQUOTE()
//{
//    return token(lexer::STRING, _STRINGS('"').c_str());
//}

token lexer::STRINGS_WITH_QUOTE(char quote)
{
    return token(lexer::STRING, _STRINGS(quote).c_str());
}

std::string lexer::_STRINGS(int ch)
{
    std::string buf;
    do
    {
        buf.push_back(c);
        consume();
      
        if (c=='\\')
        {
            buf.push_back(c);
            consume();
            buf.push_back(c);
            consume();
        }
    } while (c != ch);
    return std::string(buf);
}



token lexer::next_token()
{
    if (c0=='\''&&single_quote_number%2==1)
    {
        single_quote_number = 1;
        return STRINGS_WITH_QUOTE('\'');
    }
    if (c0=='"'&&double_quote_number % 2 == 1)
    {
        double_quote_number = 1;
        return STRINGS_WITH_QUOTE('"');
    }
    while (c!=EOF)
    {
        switch (c)
        {
        case ' ':case '\t':case '\n':case '\r':
            WS();
            continue;
        case '<':
            consume();
            if (c == '=')
            {
                consume();
                return token(LEOP, "<=");
            }
            else if (c == '-')
            {
                consume();
                return token(lexer::ARROW, "<-");
            }
            else
            {
                return token(lexer::LESSOP,"<");
            }
        case '>':
            consume();
            if (c == '=')
            {
                consume();
                return token(MEOP, ">=");
            }
            else
            {
                consume();
                return token(MOREOP, ">");
            }
        case '!':
            consume();
            if (c == '=')
            {
                consume();
                return token(NEOP, "!=");
            }
            else
            {
                consume();
                log::write_line(err_msg_mgr::invlid_token("!%c", c).c_str());
            }
        case '=':
            consume();
            return token(EQOP, "=");
        case '\'':
            ++single_quote_number;
            consume();
            return token(SINGLEQUOTE, "'");
        case '"':
            ++double_quote_number;
            consume();
            return token(DOUBLEQUOTE, "\"");
        case ',':
            consume();
            return token(COMMA, ",");
        case '[':
            consume();
            return token(LBRACKET, "[");
        case ']':
            consume();
            return token(RBRACKET, "]");
        default:
            if (isalpha(c))
            {
                return IDENTIFIERS();
            }
            if (isnum(c))
            {
                return NUMS();
            }
        }
    }
    return token(EOF_TYPE, "<EOF>");
}


lexer::lexer(const std::string& input = "") :input(input), c(input[0]), p(0), single_quote_number(0),double_quote_number(0)
{

}

lexer::~lexer()
{

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
        c0 = c;
        c = input[p];
    }
}

bool lexer::isnum(int c)
{
    int t = c - '0';
    if (t >= 0 && t <= 9)
    {
        return true;
    }
    return false;
}
//void lexer::match(char x)
//{
//    if (c==x)
//    {
//        consume();
//    }
//    else
//    {
//        std::string error_msg("expecting ");
//        error_msg.push_back(x);
//        error_msg.append("; found ");
//        error_msg.push_back(c);
//        throw std::runtime_error(error_msg);
//    }
//}



