#include "lexer.h"
#include <string>
#include <stdexcept>
#include <cctype>
#include "operation.h"
#include "log.h"
#include "err_msg_mgr.h"

const std::string lexer::token_names[] = {"N/A",
    "<EOF>", "IDENTIFIER", "SINGLEQUOTE",
    "DOUBLEQUOTE", "COMMA", "LBRACKET",
    "RBRACKET", "ARROW", "NUM",
    "BASIC_TYPE","OPERATION_TYPE","LOGIC_TYPE" };

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
std::string lexer::IDENTIFIERS()
{
    std::string buf;
    do
    {
        buf.push_back(c);
        consume();
    } while (isalnum(c));
    return std::string(buf);
}

std::string lexer::NUMS()
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
    return std::string(buf);
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
    if (!quote_stack.empty())//string_identifier.first stores the quotes
    {
        if (quote_stack.top() == c)
        {
            consume();
            char temp = quote_stack.top();
            quote_stack.pop();
            if (temp=='\'')
            {
                return token(tag::SINGLEQUOTE, "'");
            }
            return token(tag::DOUBLEQUOTE, "\"");
        }
        else
        {
            std::string id = STRINGS_WITH_TERMINATION(quote_stack.top()).c_str();
            token tk(tag::BASIC_TYPE, id.c_str());
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
            return token(tag::COMMA, ",");
        case '[':
            consume();
            return token(tag::LBRACKET, "[");
        case ']':
            consume();
            return token(tag::RBRACKET, "]");
        case '\'':
            consume();
            quote_stack.push('\'');
            return token(tag::SINGLEQUOTE, "'");
        case '"':
            consume();
            quote_stack.push('"');
            return token(tag::DOUBLEQUOTE, "\"");
        case '<':
            consume();
            if (c == '-')
            {
                consume();
                return token(tag::ARROW, "<-");
            }
            else if (c == '=')
            {
                consume();
                return token(tag::LOGIC_TYPE, "<=");
            }
            else
            {
                return token(tag::LOGIC_TYPE, "<");
            }
        case '>':
            consume();
            if (c == '=')
            {
                consume();
                return token(tag::LOGIC_TYPE, ">=");
            }
            else
            {
                return token(tag::LOGIC_TYPE,">");
            }
        case '=':
            consume();
            return token(tag::LOGIC_TYPE, "=");
        case '!':
            consume();
            if (c == '=')
            {
                consume();
                return token(tag::LOGIC_TYPE,"!=");
            }
            else
            {
                log::write_line(err_msg_mgr::invlid_expression("invalid token !%c", c).c_str());
            }
        default:
            if (isalpha(c))
            {
                 std::string id=IDENTIFIERS();
                 if (key_words.contain_key(id))
                 {
                     return token(key_words[id],id.c_str());
                 }
                 return token(tag::IDENTIFIER,id.c_str());
            }
            if (isnum(c))
            {
                 return token(tag::NUM,NUMS().c_str());
            }
        }
    }
    return token(tag::EOF_TYPE, "<EOF>");
}

lexer::lexer(const std::string& input = "") :input(input), c(input[0]), p(0)
{
    //key_words.add_key_word("'", tag::SINGLEQUOTE);
    //key_words.add_key_word("\"", tag::DOUBLEQUOTE);
    //key_words.add_key_word(",", tag::COMMA);
    //key_words.add_key_word("[", tag::LBRACKET);
    //key_words.add_key_word("]", tag::RBRACKET);
    //key_words.add_key_word("<", tag::LESSOP);
    //key_words.add_key_word(">", tag::MOREOP);
    //key_words.add_key_word("<=", tag::LEOP);
    //key_words.add_key_word(">=", tag::MEOP);
    //key_words.add_key_word("!=", tag::NEOP);
    //key_words.add_key_word("=", tag::EQOP);
    //key_words.add_key_word("<-", tag::ARROW);
    key_words.add_key_word("create", tag::OPERATION_TYPE);
    key_words.add_key_word("drop", tag::OPERATION_TYPE);
    key_words.add_key_word("alter", tag::OPERATION_TYPE);
    key_words.add_key_word("insert", tag::OPERATION_TYPE);
    key_words.add_key_word("int", tag::BASIC_TYPE);
    key_words.add_key_word("string", tag::BASIC_TYPE);
    key_words.add_key_word("double", tag::BASIC_TYPE);
}

lexer::~lexer()
{

}

void lexer::consume()
{
    ++p >= input.size() ? (c = EOF) : (c = input[p]);
}

bool lexer::isnum(int c)
{
    return (c - '0') >= 0 && (c - '0') <= 9 ? true : false;
}


