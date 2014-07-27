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

void executor(operation* o);

class evaluator
{
public:
    evaluator();
    ~evaluator();
    result_list execute_select(select_operation*);
    result_list execute_delete(delete_operation*);
    result_list execute_create(create_operation*);
    result_list execute_drop(drop_operation*);
    result_list execute_alter(alter_operation*);
    result_list execute_insert(insert_operation*);
};

