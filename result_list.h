#pragma once
#include <vector>
#include <string>

class result_list
{
public:
    typedef std::vector<std::string>::iterator result_list_iterator;
    result_list(const std::string&);
    result_list();
    ~result_list();
    void add(const std::string&);

    bool empty();
    size_t size();
    result_list_iterator begin();
    result_list_iterator end();
    std::string operator[](size_t);
private:
    std::vector<std::string> items;
};

