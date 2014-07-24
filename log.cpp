#include "log.h"
#include <iterator>
#include <iostream>
std::string log::path(file_manager::get_current_directory().append("\\ERR_LOG.log"));
err_counter log::counter;

std::string file_manager::get_current_directory()
{
    char buffer[BUFSIZ];
    GetCurrentDirectoryA(BUFSIZ, buffer);
    return std::string(buffer);
}

void log::write_line(const char* content)
{
    /*std::string str(content);
    str.append("\n");
    file.open(path);
    file.write(str);
    file.close();*/
    counter.add_error(std::string(content));
}

void log::clear()
{
    counter.clear();
}

bool log::empty()
{
    return counter.empty();
}

void log::foreach()
{
    err_counter::iterator iter = counter.begin();
    while (iter!=counter.end())
    {
        std::cout << *iter << std::endl;
        ++iter;
    }
}