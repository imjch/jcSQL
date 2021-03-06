#pragma once
#include <string>
#include "key_word_table.h"
#include <stack>

class tag
{
public:
    static const int INVALID = 0;
    static const int EOF_TYPE = 1;
    static const int IDENTIFIER = 2;
    static const int SINGLEQUOTE = 3;
    static const int DOUBLEQUOTE = 4;
    static const int COMMA = 5;
    static const int LBRACKET = 6;
    static const int RBRACKET = 7;
    static const int ARROW = 13;
    static const int INT = 14;
    static const int DOUBLE = 15;
    static const int BASIC_TYPE = 16;
    static const int AND = 17;
    static const int OR = 18;
    static const int NOT = 19;
    static const int JC_NULL = 20;
    static const int TABLE = 21;
    static const int LOGIC_TYPE = 22;
    static const int ASSIGN = 23;
    static const int STRING = 24;
    static const int UNIQUE = 25;
    static const int PRIMARY = 26;
    static const int KEY = 27;

    static const int ADD = 28;
    static const int SUB = 29;
    static const int TIMES = 30;
    static const int SLASH = 31;

    static const int JC_SELECT = 100;
    static const int JC_DELETE = 101;
    static const int JC_CREATE = 102;
    static const int JC_DROP = 103;
    static const int JC_ALTER = 104;
    static const int JC_INSERT = 105;
};

class token
{
public:
	token(int, const char*);
	~token();
    int get_token_type() const;
    std::string get_token_text() const;
    const std::string& to_string();
private:
	int type;
	std::string text;
};

class lexer
{
public:
    lexer(const std::string&);
    ~lexer();
    token next_token();
private:
    void consume();
    bool isnum(int);
    void WS();
    std::string IDENTIFIERS();
    token NUMS();
    std::string STRINGS_WITH_TERMINATION(char);
    key_word_table key_words;
    std::string input;
    char c;
    size_t p;
    std::stack<char> quote_stack;
    static const std::string token_names[];
};

