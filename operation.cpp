#include "operation.h"

operation::operation()
{
}

operation::~operation()
{
}

void operation::set_table_name(const std::string& t_name)
{
    table_name = t_name;
}

const std::string& operation::get_table_name() const
{
    return table_name;
}
