#include "dir_mgr.h"
#include <cerrno>
#include <direct.h>
#include <Windows.h>
#include <string>
#include <stdexcept>
#include <Shlwapi.h>
dir_mgr::dir_mgr()
{
}

dir_mgr::~dir_mgr()
{
}

void dir_mgr::create_directory(const std::string& path)
{
    db_path = path;
    if (CreateDirectoryA(path.c_str(), NULL) == 0)
    {
        throw std::runtime_error("creating directory error");
    } 
}

void dir_mgr::remove_dir(const std::string& path)
{
    if (RemoveDirectoryA(path.c_str())==0)
    {
        throw std::runtime_error("removing directory error");
    }
}

std::string dir_mgr::get_current_directory()
{
    char buffer[BUFSIZ];
    if (GetCurrentDirectoryA(BUFSIZ, buffer) == 0)
    {
        throw std::runtime_error("getting current directory error");
    }
    return std::string(buffer);
}

bool dir_mgr::exist(const std::string& path)
{
    if (PathFileExistsA(path.c_str())==1)
    {
        return true;
    }
    return false;
}