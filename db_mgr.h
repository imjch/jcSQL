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
    static void create_database(const std::string&);
    static void delete_database(const std::string&);
    static void set_current_database(const std::string&);
    static const std::string& get_current_database();
    static bool exist(const std::string&);
private:
    static std::string default_db;
};




