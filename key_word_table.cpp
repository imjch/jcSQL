#include "key_word_table.h"


key_word_table::key_word_table()
{
}


key_word_table::~key_word_table()
{
}



void key_word_table::add_key_word(const char* key_word, int token_type)
{
    add_key_word(std::string(key_word),token_type);
}

void key_word_table::add_key_word(std::string& key_word, int token_type)
{
    word_table.insert(std::make_pair(key_word, token_type));
}

bool key_word_table::contain_key(std::string& key)
{
    return word_table.count(key) ? true : false;
}


int key_word_table::operator[](std::string& key)
{
    word_iterator word = word_table.find(key);
    if (word != word_table.end())
    {
        return word->second;
    }
    return 0;
}

int key_word_table::operator[](char key)
{
    return operator[](std::string(&key));
}

int key_word_table::operator[](const char* key)
{
    return operator[](std::string(key));
}


