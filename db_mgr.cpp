#include "db_mgr.h"
#include <string>
#include <cassert>
#include <stdexcept>
#include "err_msg_mgr.h"
#include <iostream>
std::string db_mgr::default_db(dir_mgr::get_current_directory()+"\\jcsql");
db_mgr::db_mgr()
{
}

db_mgr::~db_mgr()
{
}

void db_mgr::create_database(const std::string& db_name)
{
    assert(db_name.size()>0);
    if (dir_mgr::exist(get_current_database()))
    {
        throw std::runtime_error(err_msg_mgr::invalid_expression("database '%s' has already existed",db_name.c_str()));
    }
    try
    {
        dir_mgr::create_directory(get_current_database());
    }
    catch (std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}


void db_mgr::delete_database(const std::string& db_name)
{
    assert(db_name.size()>0);
    if (!dir_mgr::exist(get_current_database()))
    {
        throw std::runtime_error(err_msg_mgr::invalid_expression("database '%s' non-exists", db_name.c_str()));
    }
    try
    {
        dir_mgr::remove_dir(get_current_database());
    }
    catch (std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

bool db_mgr::exist(const std::string& db_name)
{
    assert(db_name.size()>0);
    if (dir_mgr::exist(get_current_database()))
    {
        return true;
    }
    return false;
}

void db_mgr::set_current_database(const std::string& db_path)
{
    default_db = dir_mgr::get_current_directory().append("\\").append(db_path);
}

const std::string& db_mgr::get_current_database()
{
    return default_db;
}