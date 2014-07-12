#pragma once
#include "lexer.h"
#include "operation.h"
class operation_factory
{
    operation_factory();
    ~operation_factory();
public:
    static operation& get_operation(int);
};

