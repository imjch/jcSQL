#include "executor.h"
#include "select_operation.h"
#include <string>
#include "err_msg_mgr.h"
#include "table_attr.h"
#include <cstdio>
#include "table_mgr.h"
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
    if (!table_mgr::exist(o->get_table_name()))
    {
        fprintf(stderr, "table %s non-exists...\n", o->get_table_name().c_str());
        return;
    }
}

void evaluator::execute_delete(delete_operation* o)
{
    if (!table_mgr::exist(o->get_table_name()))
    {
        fprintf(stderr, "table %s non-exists...\n", o->get_table_name().c_str());
        return;
    }
}

void evaluator::execute_create(create_operation* o)
{
    if (table_mgr::exist(o->get_table_name()))
    {
        fprintf(stderr,"table %s has already existed\n",o->get_table_name().c_str());
        return;
    }
    table_mgr::create_table(o->get_table_name());
    t_mgr.open_table(o->get_table_name());
    t_mgr.set_table_attrs(o->get_table_attr());
    t_mgr.set_table_type_columns(o->get_type_column_table());
    t_mgr.close_table();
}

void evaluator::execute_drop(drop_operation* o)
{
    if (!table_mgr::exist(o->get_table_name()))
    {
        fprintf(stderr, "table %s non-exists...\n", o->get_table_name().c_str());
        return;
    }
    t_mgr.delete_table(o->get_table_name());
}

void evaluator::execute_alter(alter_operation* o)
{
    if (!table_mgr::exist(o->get_table_name()))
    {
        fprintf(stderr, "table %s non-exists...\n", o->get_table_name().c_str());
        return;
    }
    /*t_mgr.open_table(o->get_table_name());
    */
}

void evaluator::execute_insert(insert_operation* o)
{
    if (!table_mgr::exist(o->get_table_name()))
    {
        fprintf(stderr, "table %s non-exists...\n", o->get_table_name().c_str());
        return;
    }
    t_mgr.open_table(o->get_table_name());
    t_mgr.insert_data(o->get_attr_val_list());
    t_mgr.close_table();
}

