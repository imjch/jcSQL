#include "executor.h"
#include "select_operation.h"
#include <string>
#include "err_msg_mgr.h"
#include "table_attr.h"
#include <cstdio>
#include <iostream>
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

void evaluator::execute_select(select_operation* o)
{
    
}

void evaluator::execute_delete(delete_operation* o)
{

}

void evaluator::execute_create(create_operation* o)
{
    table_mgr::create_table(o->get_table_name());
    t_mgr.open_table(o->get_table_name());
    table_attr::iterator iter = table_attr::begin();
    for (; iter != table_attr::end(); iter++)
    {
        if (iter->first==PRIMARY_KEY)
        {
            t_mgr.add_attr("primary key", iter->second);
        }
        else if (iter->first == NOT_NULL)
        {
            t_mgr.add_attr("not null", iter->second);
        }
        else if (iter->first == UNIQUE)
        {
            t_mgr.add_attr("unique", iter->second);
        }
        else
        {
            throw std::runtime_error("unknown type of column");
        }
    }
}

void evaluator::execute_drop(drop_operation* o)
{

}

void evaluator::execute_alter(alter_operation* o)
{

}

void evaluator::execute_insert(insert_operation* o)
{

}

