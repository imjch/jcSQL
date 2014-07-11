#include "lexer.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include "processor.h"
#include "log.h"
#include "err_msg_mgr.h"

const std::string lexer::token_names[] = {
    "N/A", "<EOF>", "IDENTIFIER", "SINGLEQUOTE",
    "DOUBLEQUOTE", "COMMA", "LBRACKET",
    "RBRACKET", "LESSOP", "MOREOP", "LEOP",
    "MEOP", "NEOP", "EQOP", "NUM", "CHARS",
    "ARROW", "STRING" };

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
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r')
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


std::string lexer::STRINGS_WITH_TERMINATION(char ch)
{
    std::string buf;
    while (c != ch&&c != EOF)
    {
        buf.push_back(c);
        consume();
        if (c == '\\')
        {
            buf.push_back(c);
            consume();
            buf.push_back(c);
            consume();
        }
    }
    return std::string(buf);
}




token lexer::next_token()
{
    if (!string_identifier.first.empty())//string_identifier.first stores the quotes
    {
        if (string_identifier.first.top()==c)
        {
            consume();
            string_identifier.first.pop();
            return token(lexer::SINGLEQUOTE,"'");
        }
        else
        {
            std::string id = STRINGS_WITH_TERMINATION(string_identifier.first.top()).c_str();
            token tk(lexer::STRING, id.c_str());
            if (!id.empty())
            {
                return token(tk);
            }
        }
    }

    while (c != EOF)
    {
        switch (c)
        {
        case ' ':case '\t':case '\n':case '\r':
            WS();
            continue;
        case ',':
            consume();
            return token(COMMA, ",");
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
                return token(lexer::LESSOP, "<");
            }
        case '\'':
            consume();
            string_identifier.first.push('\'');
            return token(SINGLEQUOTE, "'");
        case '"':
            consume();
            string_identifier.first.push('"');
            return token(DOUBLEQUOTE, "\"");
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

lexer::lexer(const std::string& input = "") :input(input), c(input[0]), p(0)
{
    
}

lexer::~lexer()
{

}



void lexer::consume()
{
    ++p;
    if (p >= input.size())
    {
        c = EOF;
    }
    else
    {
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


