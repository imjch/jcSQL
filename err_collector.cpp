#include "err_collector.h"
#include <ostream>

std::vector<std::string> err_collector::err_container;

err_collector::err_collector()
{
}

err_collector::~err_collector()
{
}

void err_collector::output_error(std::ostream_iterator<std::string>& output)
{
    for (iterator iter = begin(); iter != end(); iter++)
    {
        *output = *iter;
    }
}

void err_collector::add_error(const std::string& str)
{
    err_container.push_back(str);
}

size_t err_collector::size()
{
    return err_container.size();
}
bool err_collector::empty()
{
    return err_container.empty();
}

void err_collector::clear()
{
    err_container.clear();
}

err_collector::iterator err_collector::begin()
{
    return err_container.begin();
}

err_collector::iterator err_collector::end()
{
    return err_container.end();
}

