#pragma once
#include <stack>
#include <string>

class char_container
{
public:
    char_container();
    ~char_container();
    char last_char();
    void discard_last_char();
    void put_char(int c);
    bool is_empty();
 
private:
    std::stack<char> items;
};

