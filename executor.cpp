#include "executor.h"
#include "select_operation.h"

void executor(operation* o)
{
    evaluator eval;
    if (auto op = dynamic_cast<select_operation*>(o))
    {
        eval.execute_select(op);
    }
    else if (auto op = dynamic_cast<delete_operation*>(o))
    {
        eval.execute_delete(op);
    }
    else if (auto op = dynamic_cast<create_operation*>(o))
    {
        eval.execute_create(op);
    }
    else if (auto op = dynamic_cast<drop_operation*>(o))
    {
        eval.execute_drop(op);
    }
    else if (auto op = dynamic_cast<alter_operation*>(o))
    {
        eval.execute_alter(op);
    }
    else if (auto op = dynamic_cast<insert_operation*>(o))
    {
        eval.execute_insert(op);
    }
    else
    {
        throw std::bad_cast("invalid type of operation");
    }
}

evaluator::evaluator()
{
}


evaluator::~evaluator()
{
}

result_list evaluator::execute_select(select_operation* o)
{
    
}

result_list evaluator::execute_delete(delete_operation* o)
{

}

result_list evaluator::execute_create(create_operation* o)
{

}

result_list evaluator::execute_drop(drop_operation* o)
{

}

result_list evaluator::execute_alter(alter_operation* o)
{

}

result_list evaluator::execute_insert(insert_operation* o)
{

}

