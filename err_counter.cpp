#include "err_counter.h"
#include <ostream>
err_counter::err_counter() :count(0)
{
}

err_counter::~err_counter()
{
}

void err_counter::add_error(const std::string& str)
{
    err_container.push_back(str);
}

size_t err_counter::size()
{
    return err_container.size();
}
bool err_counter::empty()
{
    return err_container.empty();
}

void err_counter::clear()
{
    err_container.clear();
}

err_counter::iterator err_counter::begin()
{
    return err_container.begin();
}

err_counter::iterator err_counter::end()
{
    return err_container.end();
}

