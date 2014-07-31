#include "dir_mgr.h"
#include <cerrno>
#include <cassert>
#include <Windows.h>
#include <string>
#include "err_msg_mgr.h"
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
    assert(path.size()>0);
    if (CreateDirectoryA(path.c_str(), NULL) == 0)
    {
        throw std::runtime_error(err_msg_mgr::invalid_expression("creating directory '%s' error",path.c_str()));
    } 
}

void dir_mgr::remove_dir(const std::string& path)
{
    assert(path.size()>0);
    if (RemoveDirectoryA(path.c_str())==0)
    {
        throw std::runtime_error(err_msg_mgr::invalid_expression("removing directory '%s' error", path.c_str()));
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
    assert(path.size()>0);
    GetFileAttributesA(path.c_str()); // from winbase.h
    if (INVALID_FILE_ATTRIBUTES == GetFileAttributesA(path.c_str()) && GetLastError() == ERROR_FILE_NOT_FOUND)
    {
        return false;
    }
    return true;
}