#include "processor_factory.h"
#include "lexer.h"
#include "processor.h"
#include "processor_set.h"
#include <stdexcept>
#include <assert.h>

processor_factory::processor_factory()
{
}


processor_factory::~processor_factory()
{

}

processor& processor_factory::get_processor(int processor_type)
{
    //todo
}

int processor::get_processor_type() const
{
    return type;
}