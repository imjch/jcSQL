#pragma once
#include <string>
#include <tuple>
class token
{
public:
	token(int, const char*);
    token(int c){};
	~token();

    int get_token_type();
    const std::string& to_string();

private:
	int type;
	std::string text;
};


class lexer
{
public:

    void WS();
    token IDENTIFIERS();
    token NUMS();
    //token STRINGS_WITH_SINGLEQUOTE();
    token STRINGS_WITH_QUOTE(char);
    static const std::string get_token_name(int type);
    token next_token();
    
    lexer(const std::string&);
    ~lexer();

    static const int EOF_TYPE = 1;
    static const int IDENTIFIER = 2;
    static const int SINGLEQUOTE = 3;
    static const int DOUBLEQUOTE = 4;
    static const int COMMA = 5;
    static const int LBRACKET = 6;
    static const int RBRACKET = 7;
    static const int LESSOP = 8;
    static const int MOREOP = 9;
    static const int LEOP = 10;
    static const int MEOP = 11;
    static const int NEOP = 12;
    static const int EQOP = 13;
    static const int NUM = 14;
    static const int CHARS = 15;
    static const int ARROW = 16;
    static const int STRING = 17;
private:
    void consume();
    bool isnum(int);
    std::string _STRINGS(int);
    static const std::string token_names[];

    std::string input;
    char c;
    char c0;
    size_t p;
    size_t single_quote_number;
    size_t double_quote_number;
};

