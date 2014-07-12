#pragma once
#include <cstdio>
#include <fstream>
#include <string>
#include <stdexcept>
#include <Windows.h>


class file_manager
{
public:
    file_manager(const std::string& path) :file_path(path), file(path, std::fstream::out | std::fstream::app)
    {
        is_success();
    }

    file_manager()
    {
    }

    ~file_manager()
    {
    }

    void open(const std::string& path)
    {
        file_path = path;
        if (!file.is_open())
        {
            file.open(file_path, std::fstream::out | std::fstream::app);
            is_success();
        }
    }

    void clear()
    {
        file.close();
        if (remove(file_path.c_str()) != 0)
        {
            throw std::runtime_error("clear file error...");
        }
        file.open(file_path, std::fstream::out | std::fstream::app);
    }

    void close()
    {
        if (file.is_open())
        {
            file.close();
        }
    }

    void write(const std::string& content)
    {
        file.write(content.c_str(), content.size());
    }

    static std::string get_current_directory();
private:
    void is_success()
    {
        if (!file)
        {
            throw std::runtime_error("unable to open the file");
        }
    }
    std::fstream file;
    std::string file_path;
};


class log
{
public:
    static void write_with_clear(const char*);
    static void write_append(const char*);
    static void write_line(const char*);

private:
    static std::string path;
    static file_manager file;
};
