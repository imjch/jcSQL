#pragma once
#include <string>
#include "uncopyable.h"

class dir_mgr :private uncopyable
{
public:
    dir_mgr();
    ~dir_mgr();
    void create_directory(const std::string&);
    static std::string get_current_directory();
    void remove_dir(const std::string&);
    bool exist(const std::string&);
private:
    std::string db_path;
};

