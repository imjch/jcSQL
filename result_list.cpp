#include "result_list.h"
#include <cassert>

result_list::result_list()
{
}

result_list::result_list(const std::string& item)
{
    items.push_back(item);
}

result_list::~result_list()
{
}

void result_list::add(const std::string& item)
{
    items.push_back(item);
}

result_list::result_list_iterator result_list::begin()
{
    return items.begin();
}

result_list::result_list_iterator result_list::end()
{
    return items.end();
}

size_t result_list::size()
{
    return items.size();
}

std::string result_list::operator[](size_t index)
{
    assert(index>=0);
    return items[index];
}

bool result_list::empty()
{
    return items.empty();
}

