#pragma once
#include <unordered_map>
#include <utility>
#include <string>
class key_word_table
{
public:
    key_word_table();
    ~key_word_table();

    bool contain_key(std::string&);
    void add_key_word(const char*,int);
    void add_key_word(std::string&, int);
    int operator[](const char*);
    int operator[](std::string&);
    int operator[](char);
private:
    typedef std::unordered_map<std::string, int> table;
    typedef table::iterator word_iterator;
    table word_table;
};

