#include "drop_operation.h"


drop_operation::drop_operation()
{
}

drop_operation::~drop_operation()
{
    operation::~operation();
}

drop_operation::drop_operation(const std::string& t_name)
{
    operation::set_table_name(t_name);
}
//
//result_list drop_operation::execute()
//{
//    return result_list("sss");
//}

