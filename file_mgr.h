#pragma once
#include <string>
#include <fstream>
#include "uncopyable.h"
class file_mgr:private uncopyable
{
public:
    file_mgr(const std::string&, const char*);
    ~file_mgr();
    file_mgr();
    void clear_content();
    std::string read();
    void write(const std::string&);
    void append(const std::string&);
    static void create_file(const std::string&);
    static void remove_file(const std::string&);
    static bool exist(const std::string&);
    bool is_open();
    void close();
    void open(const std::string&, const char * fmode);
private:

    FILE* fp;
    std::string file_path;
    std::string open_mode;
};

