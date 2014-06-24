#pragma once
#include <string>
#include <memory>
class token
{
public:
	token(int, const char*);
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

    static const std::string get_token_name(int type);

    void WS();//ignoring the irrelevant characters;
    token TNAME();
    token next_token();
    lexer(const std::string&);
    ~lexer();

    static const int EOF_TYPE = 1;
    static const int NAME = 2;
    static const int SINGLEQUOTE = 3;
    static const int DOUBLEQUOTE = 4;
    static const int COMMA = 5;
    static const int LPARENTHESIS= 6;
    static const int RPARENTHESIS = 7;

private:
    void consume();
    void match(char);

    static const std::string token_names[];
    std::string input;
    char c;
    int p;
};

