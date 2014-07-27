#pragma once
#include <vector>
#include <string>
#include <iterator>
class err_collector
{
public:
    typedef std::vector<std::string>::iterator iterator;
    
    static void output_error(std::ostream_iterator<std::string>&);
    static void add_error(const std::string&);
    static size_t size();
    static bool empty();
    static void clear();
    static iterator begin();
    static iterator end();
private:
    err_collector();
    ~err_collector();
    static std::vector<std::string> err_container;
};

