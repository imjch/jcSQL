#include "log.h"

std::string log::path(file_manager::get_current_directory().append("\\ERR_LOG.log"));
file_manager log::file;

std::string file_manager::get_current_directory()
{
    char buffer[BUFSIZ];
    GetCurrentDirectoryA(BUFSIZ, buffer);
    return std::string(buffer);
}

void log::write_append(const char* content)
{
    file.open(path);
    file.write(content);
    file.close();
}

void log::write_line(const char* content)
{
    std::string str(content);
    str.append("\n");
    file.open(path);
    file.write(str);
    file.close();
}

void log::clear()
{
    file.open(path);
    file.clear();
    file.close();
}