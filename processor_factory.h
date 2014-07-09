#pragma once
#include "lexer.h"
#include "processor.h"
class processor_factory
{
    processor_factory();
    ~processor_factory();
public:
    static processor& get_processor(int);
};

