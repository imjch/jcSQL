#pragma once
#include "json\json.h"
#include <list>
#include <string>
#include <map>
class primary_key
{
public:
    typedef std::string primary_key_val;
    primary_key();
    ~primary_key();
    void insert(const std::string&, primary_key_val&);
    primary_key_val get_primary_key_val(const std::string&);
    size_t size();
    bool empty();
    std::string to_string();
private:
    std::map<std::string, primary_key_val> keys;
};

