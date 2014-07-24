#pragma once
#include <vector>
#include <string>

class err_counter
{
public:
    typedef std::vector<std::string>::iterator iterator;
    err_counter();
    ~err_counter();
    void add_error(const std::string&);
    size_t size();
    bool empty();
    void clear();
    
    iterator begin();
    iterator end();
private:
    int  count;
    std::vector<std::string> err_container;
};

