#pragma once
#include "operation.h"
#include "result_list.h"
#include "select_operation.h"
#include "delete_operation.h"
#include "create_operation.h"
#include "drop_operation.h"
#include "alter_operation.h"
#include "insert_operation.h"
#include <stdexcept>

void executor(operation* o)
{

    if (auto op = dynamic_cast<select_operation*>(o))
    {
        
    }
    else if (auto op = dynamic_cast<delete_operation*>(o))
    {

    }
    else if (auto op = dynamic_cast<create_operation*>(o))
    {

    }
    else if (auto op = dynamic_cast<drop_operation*>(o))
    {

    }
    else if (auto op = dynamic_cast<alter_operation*>(o))
    {

    }
    else if (auto op = dynamic_cast<insert_operation*>(o))
    {

    }
    else
    {
        throw std::bad_cast("invalid type of operation");
    }
}

class evaluator
{
public:
    evaluator();
    ~evaluator();
    result_list execute(operation*, select_operation);
};

