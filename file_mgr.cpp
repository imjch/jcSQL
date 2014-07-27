#include "file_mgr.h"
#include "err_msg_mgr.h"
#include <Shlwapi.h>

file_mgr::file_mgr()
{
}

file_mgr::~file_mgr()
{
}

bool file_mgr::exist(const std::string& path)
{
    if (PathFileExistsA(path.c_str()))
    {
        return true;
    }
    return false;
}

void file_mgr::open(const std::string& path)
{
    file_path = path;
    if (!exist(path))
    {
        throw std::runtime_error("file non-exist");
    }
    if (!file.is_open())
    {
        try
        {
            file.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
            is_success();
        }
        catch (...)
        {
            throw;
        }
    }
}

void file_mgr::clear()
{
    if (!file_path.empty())
    {
        close();
        if (remove(file_path.c_str()) != 0)
        {
            throw std::runtime_error("clear file error");
        }
        create_file(file_path);
    }
}

void file_mgr::close()
{
    if (file.is_open())
    {
        file.close();
    }
}

void file_mgr::write(const std::string& content)
{
    if (!file_path.empty())
    {
        try
        {
            file.write(content.c_str(), content.size());
        }
        catch (...)
        {
            throw;
        }
    }
}

void file_mgr::is_success()
{
    if (!file)
    {
        throw std::runtime_error(err_msg_mgr::invalid_expression("unable to open the file %s",file_path.c_str()).c_str());
    }
} 

void file_mgr::create_file(const std::string& path)
{
    if (!exist(path))
    {
        std::ofstream fs(path.c_str());
        is_success();
    }
}
