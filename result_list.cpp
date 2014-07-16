#include "result_list.h"


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

