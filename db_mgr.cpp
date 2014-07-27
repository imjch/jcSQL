#include "db_mgr.h"
#include <string>
#include <direct.h>
#include <Windows.h>

db_mgr::db_mgr() :default_dir(dir_mgr::get_current_directory())
{
}

db_mgr::~db_mgr()
{
}

std::string db_mgr::to_dir(const std::string& db_name)
{
    return default_dir +"/" + db_name;
}

void db_mgr::create_database(const std::string& db_name)
{
    if (d_mgr.exist(to_dir(db_name)))
    {
        throw std::runtime_error("database exists.");
    }
    try
    {
        d_mgr.create_directory(to_dir(db_name));
    }
    catch (...)
    {
        throw;
    }
}


void db_mgr::delete_database(const std::string& db_name)
{
    if (!d_mgr.exist(to_dir(db_name)))
    {
        throw std::runtime_error("database non-exists.");
    }
    try
    {
        d_mgr.remove_dir(to_dir(db_name));
    }
    catch (...)
    {
        throw;
    }
}

bool db_mgr::exist(const std::string& db_name)
{
    if (d_mgr.exist(to_dir(db_name)))
    {
        return true;
    }
    return false;
}