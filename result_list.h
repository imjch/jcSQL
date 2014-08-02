#pragma once
#include <list>
#include <string>
class result_list
{
public:
    typedef std::list<std::string>::iterator result_list_iterator;
    result_list(const std::string&);
    result_list();
    ~result_list();
    void add(const std::string&);

    size_t size();
    result_list_iterator begin();
    result_list_iterator end();
private:
    std::list<std::string> items;
};

