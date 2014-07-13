#include "lexer.h"
#include <string>
#include <stdexcept>
#include <cctype>

#include "log.h"
#include "err_msg_mgr.h"
#include "cctype"

//const std::string lexer::token_names[] = {"N/A",
//    "<EOF>", "IDENTIFIER", "SINGLEQUOTE",
//    "DOUBLEQUOTE", "COMMA", "LBRACKET",
//    "RBRACKET", "ARROW", "NUM",
//    "BASIC_TYPE","OPERATION_TYPE","LOGIC_TYPE" };

token::token(int type, const char* text) :type(type), text(text)
{

}

token::~token()
{

}

int token::get_token_type() const
{
    return type;
}
std::string token::get_token_text() const
{
    return text;
}

const std::string& token::to_string()
{
    text.insert(0, "<'").append("',").append(text).push_back('>');
    return text;
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
        buf.push_back(toupper(c));
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
                return token(tag::LEOP, "<=");
            }
            else
            {
                return token(tag::LESSOP, "<");
            }
        case '>':
            consume();
            if (c == '=')
            {
                consume();
                return token(tag::MEOP, ">=");
            }
            else
            {
                return token(tag::MOREOP,">");
            }
        case '=':
            consume();
            return token(tag::EQOP, "=");
        case '!':
            consume();
            if (c == '=')
            {
                consume();
                return token(tag::NEOP,"!=");
            }
            else
            {
                log::write_line(err_msg_mgr::invlid_expression("invalid token !%c", c).c_str());
            }
        default:
            if (isalpha(c))
            {
                 std::string token_text=IDENTIFIERS();
                 if (key_words.contain_key(token_text))
                 {
                     return token(key_words[token_text], token_text.c_str()); 
                 }
                 return token(tag::IDENTIFIER, token_text.c_str());
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
    key_words.add_key_word("OR", tag::OR);
    key_words.add_key_word("AND", tag::AND);
    key_words.add_key_word("NOT", tag::NOT);
    key_words.add_key_word("NULL", tag::JC_NULL);
    key_words.add_key_word("SELECT", tag::JC_SELECT);
    key_words.add_key_word("DELETE", tag::JC_DELETE);
    key_words.add_key_word("CREATE", tag::JC_CREATE);
    key_words.add_key_word("DROP", tag::JC_DROP);
    key_words.add_key_word("ALTER", tag::JC_ALTER);
    key_words.add_key_word("INSERT", tag::JC_INSERT);
    key_words.add_key_word("INT", tag::BASIC_TYPE);
    key_words.add_key_word("STRING", tag::BASIC_TYPE);
    key_words.add_key_word("DOUBLE", tag::BASIC_TYPE);
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


