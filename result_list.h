#pragma once
#include <vector>
#include <string>

class result_list
{
public:
    typedef std::vector<std::string>::iterator iterator;
    result_list();
    ~result_list();
    void add(const std::string&);
    bool empty();
    size_t size();
    iterator begin();
    iterator end();
    std::string& operator[](size_t);
private:
    std::vector<std::string> items;
};

