#pragma once
#include <string>
#include <fstream>
#include "uncopyable.h"
class file_mgr:private uncopyable
{
public:
    file_mgr();
    ~file_mgr();
    void open(const std::string&);
    bool exist(const std::string&);
    void clear();
    void close();
    void write(const std::string&);
    void create_file(const std::string&);
private:
    void is_success();
    std::fstream file;
    std::string file_path;
};

