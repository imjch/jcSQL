#pragma once
#include "uncopyable.h"
#include <string>
#include "dir_mgr.h"

//managering the dir which represents the single database
class db_mgr:private uncopyable
{
public:
    db_mgr();
    ~db_mgr();
    void create_database(const std::string&);
    void delete_database(const std::string&);
    bool exist(const std::string&);
private:
    std::string to_dir(const std::string& db_name);
    std::string default_dir;
    dir_mgr d_mgr;
};




