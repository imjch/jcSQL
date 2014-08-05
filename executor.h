#pragma once
#include "operation.h"
#include "result_list.h"
#include "select_operation.h"
#include "delete_operation.h"
#include "create_operation.h"
#include "drop_operation.h"
#include "alter_operation.h"
#include "insert_operation.h"
#include "table_mgr.h"
#include "db_mgr.h"
#include <stdexcept>

void executor(operation* o);

class evaluator
{
public:
    evaluator();
    ~evaluator();
    void init_table_attr(operation*);
    void execute_select(select_operation*);
    void execute_delete(delete_operation*);
    void execute_create(create_operation*);
    void execute_drop(drop_operation*);
    void execute_alter(alter_operation*);
    void execute_insert(insert_operation*);
private:
    void table_exist();

    table_mgr t_mgr;
    db_mgr d_mgr;
};

